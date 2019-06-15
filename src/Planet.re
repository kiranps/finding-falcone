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
      Http.get("/planets")
      |> then_(json => json |> Decode.planetList |> resolve)
    );
};