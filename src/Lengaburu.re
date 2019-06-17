open Js.Promise;
open Mission;
open Utils;

module Lengaburu = {
  [@react.component]
  let make = (~children) =>
    <div className="flex flex-col justify-center items-center pt-40">
      children
    </div>;
};
module SpaceStation = {
  [@react.component]
  let make = (~children) => <div className="flex h-40 w-3/4"> children </div>;
};

module LaunchPad = {
  [@react.component]
  let make = (~children) => <div className="flex-1"> children </div>;
};

module TimeTaken = {
  [@react.component]
  let make = (~label) =>
    <div className="text-center h-12">
      {React.string("Time taken " ++ label)}
    </div>;
};

module FindFalcone = {
  [@react.component]
  let make = (~disabled, ~onClick) => {
    let className =
      disabled
        ? "btn-blue pointer-events-none opacity-25" : "btn-blue outline-none";

    <button className onClick> {React.string("Find Falcone")} </button>;
  };
};

[@react.component]
let make = _ => {
  let (vehicles, setVehicles) = React.useState(_ => []);
  let (planets, setPlanets) = React.useState(_ => []);
  let (missions, setMission) = React.useState(_ => [None, None, None, None]);

  React.useEffect0(() => {
    let _ =
      Planet.Api.fetchPlanets()
      |> then_(json => json |> (json => setPlanets(_ => json)) |> resolve);

    let _ =
      Vehicle.Api.fetchVehicles()
      |> then_(json => json |> (json => setVehicles(_ => json)) |> resolve);

    Some(() => ());
  });

  let totalTimeTaken =
    missions
    |> List.fold_left(
         (total, mission) =>
           switch (mission) {
           | Some(mission) =>
             switch (mission.vehicle) {
             | Some(vehicle) =>
               switch (Vehicle.speed(vehicle, vehicles)) {
               | Some(speed) =>
                 total + Planet.distance(mission.planet, planets) / speed
               | None => total
               }
             | None => total
             }
           | None => total
           },
         0,
       )
    |> string_of_int;

  let isReadyToLaunch =
    missions
    |> List.for_all(mission =>
         Belt.Option.(mapWithDefault(mission, false, x => isSome(x.vehicle)))
       );

  let launchVehicles = _ => {
    let initialPayload: Falcone.payload = {
      planet_names: [],
      vehicle_names: [],
    };
    let _ =
      missions
      |> List.fold_left(
           (payload: Falcone.payload, mission) =>
             switch (mission) {
             | Some(mission) =>
               switch (mission.vehicle) {
               | Some(vehicle) => {
                   vehicle_names: [vehicle, ...payload.vehicle_names],
                   planet_names: [mission.planet, ...payload.planet_names],
                 }

               | None => payload
               }
             | None => payload
             },
           initialPayload,
         )
      |> (
        payload =>
          Falcone.Api.findFalcone(payload)
          |> then_(json =>
               json
               |> (
                 (json: Falcone.payloadResult) =>
                   (
                     switch (json.status) {
                     | "success" =>
                       switch (json.planet_name) {
                       | Some(planet) =>
                         ReasonReactRouter.push(
                           "#/result?status=success&planet="
                           ++ planet
                           ++ "&time="
                           ++ totalTimeTaken,
                         )
                       | None => ()
                       }
                     | _ => ReasonReactRouter.push("#/result?status=failed")
                     }
                   )
                   |> resolve
               )
             )
      );
    ();
  };

  let selectPlanet = (value, i) => {
    let _ =
      missions
      |> Array.of_list
      |> updateArray(Some({planet: value, vehicle: None}), i)
      |> Array.to_list
      |> (values => setMission(_ => values));
    ();
  };

  let selectVehicle = (value, i) => {
    let _ =
      missions
      |> Array.of_list
      |> (
        values => {
          switch (values[i]) {
          | Some(mission) =>
            updateArray(Some({...mission, vehicle: value}), i, values)
          | None => values
          };
        }
      )
      |> Array.to_list
      |> (values => setMission(_ => values));
    ();
  };

  let remainingPlanets =
    Utils.difference(
      List.map((planet: Planet.t) => planet.name, planets),
      missions
      |> List.filter(x => x !== None)
      |> List.map(mission =>
           switch (mission) {
           | Some(mission) => mission.planet
           | None => ""
           }
         ),
    );

  <Lengaburu>
    <SpaceStation>
      {missions
       |> List.mapi((i, mission) =>
            <LaunchPad key={string_of_int(i)}>
              <Select
                values=remainingPlanets
                onChange={value => selectPlanet(value, i)}
              />
              {switch (mission) {
               | Some(mission) =>
                 vehicles
                 |> List.mapi((j, vehicle: Vehicle.t) =>
                      <Vehicle
                        key={string_of_int(j)}
                        name={vehicle.name}
                        count={
                          vehicle.total_no
                          - Mission.vehiclesUsed(missions, vehicle.name)
                        }
                        disable={
                          vehicle.total_no
                          - Mission.vehiclesUsed(missions, vehicle.name) == 0
                          || vehicle.max_distance
                          < Planet.distance(mission.planet, planets)
                        }
                        selected={
                          switch (mission.vehicle) {
                          | Some(name) => name == vehicle.name
                          | None => false
                          }
                        }
                        onClick={_ => selectVehicle(Some(vehicle.name), i)}
                      />
                    )
                 |> Array.of_list
                 |> React.array
               | None => React.null
               }}
            </LaunchPad>
          )
       |> Array.of_list
       |> React.array}
    </SpaceStation>
    <TimeTaken label=totalTimeTaken />
    <FindFalcone disabled={!isReadyToLaunch} onClick=launchVehicles />
  </Lengaburu>;
};