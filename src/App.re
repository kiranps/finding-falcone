open Js.Promise;

module FindFalcone = {
  [@react.component]
  let make = _ =>
    <button className="outline-none block">
      {React.string("Find Falcone")}
    </button>;
};

type mission = {
  vehicle: string,
  planet: string,
};

module LaunchPad = {
  [@react.component]
  let make = (~children) => <div className="flex-1"> children </div>;
};

module Lengaburu = {
  [@react.component]
  let make = (~children) =>
    <div className="flex items-start"> children </div>;
};

let updateArray = (value, index, arr) => {
  arr[index] = value;
  arr;
};

[@react.component]
let make = _ => {
  let (vehicles, setVehicles) = React.useState(_ => []);
  let (planets, setPlanets) = React.useState(_ => []);
  let (missions, setMission) = React.useState(_ => [None, None, None, None]);

  React.useEffect0(() => {
    Js.log("didMount");
    let _ =
      Planet.Api.fetchPlanets()
      |> then_(json => json |> (json => setPlanets(_ => json)) |> resolve);

    let _ =
      Vehicle.Api.fetchVehicles()
      |> then_(json => json |> (json => setVehicles(_ => json)) |> resolve);

    Some(() => ());
  });

  let handleSelect = (value, i) => {
    let _ =
      missions
      |> Array.of_list
      |> updateArray(Some({planet: value, vehicle: ""}), i)
      |> Array.to_list
      |> (values => setMission(_ => values));
    ();
  };

  let _ = Js.log("render");

  <Lengaburu>
    {missions
     |> List.mapi((i, mission) =>
          <LaunchPad key={string_of_int(i)}>
            {planets
             |> List.map((planet: Planet.t) => planet.name)
             |> (
               values =>
                 <Select values onChange={value => handleSelect(value, i)} />
             )}
            {switch (mission) {
             | Some(x) =>
               vehicles
               |> List.mapi((i, vehicle: Vehicle.t) =>
                    <Vehicle key={string_of_int(i)} data=vehicle />
                  )
               |> Array.of_list
               |> React.array
             | None => React.null
             }}
          </LaunchPad>
        )
     |> Array.of_list
     |> React.array}
    <FindFalcone />
  </Lengaburu>;
};