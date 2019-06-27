open Js.Promise;
open Mission;
open Utils;

module Lengaburu = {
  [@react.component]
  let make = (~children) =>
    <div
      className="flex flex-col min-h-screen  items-center text-gray-700 text-base pt-24 pb-12 px-2">
      children
    </div>;
};
module SpaceStation = {
  [@react.component]
  let make = (~children) =>
    <div className="flex flex-wrap mx-auto justify-center"> children </div>;
};

module LaunchPad = {
  [@react.component]
  let make = (~children) =>
    <div className="w-full md:w-1/3 lg:w-64 rounded m-4 bg-white">
      children
    </div>;
};

module Vehicles = {
  [@react.component]
  let make = (~children) =>
    <div className="shadow rounded  overflow-hidden"> children </div>;
};

module TimeTaken = {
  [@react.component]
  let make = (~label) =>
    <div className="text-center my-6">
      {React.string("Time taken " ++ string_of_int(label))}
    </div>;
};

module FindFalcone = {
  [@react.component]
  let make = (~disabled, ~onClick) => {
    let className =
      "mb-8 "
      ++ (disabled ? "btn pointer-events-none opacity-25" : "btn outline-none");

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
        values =>
          switch (values[i]) {
          | Some(mission) =>
            updateArray(Some({...mission, vehicle: value}), i, values)
          | None => values
          }
      )
      |> Array.to_list
      |> (values => setMission(_ => values));
    ();
  };

  let remainingPlanets = Mission.remainingPlanets(missions, planets);

  let totalTimeTaken = Mission.totalTimeTaken(missions, vehicles, planets);

  let isReadyToLaunch = isReadyToLaunch(missions);

  let launchVehicles = _ => Mission.launchVehicles(missions, totalTimeTaken);

  <Lengaburu>
    <SpaceStation>
      {
        missions
        |> List.mapi((i, mission) =>
             <LaunchPad key={string_of_int(i)}>
               {
                 switch (mission) {
                 | Some(mission) =>
                   <Planet
                     name={mission.planet}
                     planets=remainingPlanets
                     onChange=(value => selectPlanet(value, i))
                   />
                 | None =>
                   <Planet
                     planets=remainingPlanets
                     onChange=(value => selectPlanet(value, i))
                   />
                 }
               }
               {
                 switch (mission) {
                 | Some(mission) =>
                   <Vehicles>
                     {
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
                                - Mission.vehiclesUsed(
                                    missions,
                                    vehicle.name,
                                  )
                                == 0
                                || vehicle.max_distance
                                < Planet.distance(mission.planet, planets)
                              }
                              selected={
                                switch (mission.vehicle) {
                                | Some(name) => name == vehicle.name
                                | None => false
                                }
                              }
                              onClick=(
                                _ => selectVehicle(Some(vehicle.name), i)
                              )
                            />
                          )
                       |> Array.of_list
                       |> React.array
                     }
                   </Vehicles>
                 | None => React.null
                 }
               }
             </LaunchPad>
           )
        |> Array.of_list
        |> React.array
      }
    </SpaceStation>
    <TimeTaken label=totalTimeTaken />
    <FindFalcone disabled={!isReadyToLaunch} onClick=launchVehicles />
  </Lengaburu>;
};