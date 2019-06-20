open Js.Promise;
type t = {
  vehicle: option(string),
  planet: string,
};

let updateCounter = (dict, key) => {
  let newCount = Belt.Option.getWithDefault(Js.Dict.get(dict, key), 0) + 1;
  Js.Dict.set(dict, key, newCount);
  Some(dict);
};

let vehiclesUsed = (missions, key) => {
  missions
  |> List.fold_left(
       (dict, mission) =>
         mission
         |> Belt.Option.flatMap(_, (mission: t) => mission.vehicle)
         |> Belt.Option.flatMap(_, updateCounter(dict))
         |> Belt.Option.getWithDefault(_, dict),
       Js.Dict.empty(),
     )
  |> Js.Dict.get(_, key)
  |> Belt.Option.getWithDefault(_, 0);
};

let isReadyToLaunch = missions =>
  missions
  |> List.for_all(mission =>
       Belt.Option.(mapWithDefault(mission, false, x => isSome(x.vehicle)))
     );

let logger = x => {
  Js.log(x);
  x;
};
let totalTimeTaken = (missions, vehicles, planets) => {
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
     );
};
let launchVehicles = (missions, timeTaken) => {
  let initialPayload: Falcone.payload = {planet_names: [], vehicle_names: []};
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
                         ++ string_of_int(timeTaken),
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

let remainingPlanets = (missions, planets) =>
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