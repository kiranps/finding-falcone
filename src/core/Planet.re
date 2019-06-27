type t = {
  name: string,
  distance: int,
};

module Decode = {
  let planet = json =>
    Json.Decode.{
      name: json |> field("name", string),
      distance: json |> field("distance", int),
    };

  let planetList = Json.Decode.list(planet);
};

module Api = {
  let fetchPlanets = () =>
    Js.Promise.(
      Http.get(Config.baseUrl ++ "/planets")
      |> then_(json => json |> Decode.planetList |> resolve)
    );
};

let distance = (planet, planets) =>
  planets
  |> List.find(x => x.name === planet)
  |> (
    result =>
      switch (result) {
      | planet => planet.distance
      | exception Not_found => 0
      }
  );

[@react.component]
let make = (~name=?, ~planets, ~onChange) =>
  <div className="w-full rounded shadow bg-teal-400">
    {
      switch (name) {
      | Some(planet) =>
        <img
          className="h-32 p-4 m-auto"
          src={"/images/" ++ planet ++ ".png"}
        />
      | None =>
        <img
          className="h-32 p-4 m-auto opacity-25"
          src="/images/placeholder.png"
        />
      }
    }
    <Select values=planets onChange />
  </div>;