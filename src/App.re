open Js.Promise;

module FindFalcone = {
  [@react.component]
  let make = _ =>
    <button className="outline-none block">
      {React.string("Find Falcone")}
    </button>;
};

type mission = {
  vehicle: option(string),
  planet: string,
};

module LaunchPad = {
  [@react.component]
  let make = (~children) => <div className="flex-1"> children </div>;
};

module Lengaburu = {
  [@react.component]
  let make = (~children) => <div className=""> children </div>;
};
module SpaceStation = {
  [@react.component]
  let make = (~children) =>
    <div className="flex items-start"> children </div>;
};

let updateArray = (value, index, arr) => {
  arr[index] = value;
  arr;
};

let getValueOrDefault = (dict, key, default) =>
  switch (Js.Dict.get(dict, key)) {
  | Some(value) => value
  | None => default
  };

let planetDistance = (planet, planets) => {
  planets
  |> List.find((x: Planet.t) => x.name === planet)
  |> (
    result =>
      switch (result) {
      | planet => planet.distance
      | exception Not_found => 0
      }
  );
};

let vehicleSpeed = (vehicleName, vehicles) => {
  vehicles
  |> List.find((x: Vehicle.t) => x.name === vehicleName)
  |> (
    result =>
      switch (result) {
      | vehicle => Some(vehicle.speed)
      | exception Not_found => None
      }
  );
};
let vehiclesUsed = (missions, key) => {
  let counter = Js.Dict.empty();
  let _ =
    missions
    |> List.iter(mission =>
         switch (mission) {
         | Some(mission) =>
           switch (mission.vehicle) {
           | Some(vehicle) =>
             Js.Dict.set(
               counter,
               vehicle,
               getValueOrDefault(counter, vehicle, 0) + 1,
             )
           | None => ()
           }
         | None => ()
         }
       );
  switch (Js.Dict.get(counter, key)) {
  | Some(int) => int
  | None => 0
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

  let totalTimeTaken =
    missions
    |> List.fold_left(
         (total, mission) =>
           switch (mission) {
           | Some(mission) =>
             switch (mission.vehicle) {
             | Some(vehicle) =>
               switch (vehicleSpeed(vehicle, vehicles)) {
               | Some(speed) =>
                 total + planetDistance(mission.planet, planets) / speed
               | None => total
               }
             | None => total
             }
           | None => total
           },
         0,
       )
    |> string_of_int;

  <Lengaburu>
    <SpaceStation>
      {missions
       |> List.mapi((i, mission) =>
            <LaunchPad key={string_of_int(i)}>
              {planets
               |> List.map((planet: Planet.t) => planet.name)
               |> (
                 values =>
                   <Select
                     values
                     onChange={value => selectPlanet(value, i)}
                   />
               )}
              {switch (mission) {
               | Some(mission) =>
                 vehicles
                 |> List.mapi((j, vehicle: Vehicle.t) =>
                      <Vehicle
                        key={string_of_int(j)}
                        name={vehicle.name}
                        count={
                          vehicle.total_no
                          - vehiclesUsed(missions, vehicle.name)
                        }
                        disable={
                          vehicle.total_no
                          - vehiclesUsed(missions, vehicle.name) == 0
                          || vehicle.max_distance
                          < planetDistance(mission.planet, planets)
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
    <div> {React.string(totalTimeTaken)} </div>
    <FindFalcone />
  </Lengaburu>;
};