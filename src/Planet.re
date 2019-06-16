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
      Http.get("https://findfalcone.herokuapp.com/planets")
      |> then_(json => json |> Decode.planetList |> resolve)
    );
};

let distance = (planet, planets) => {
  planets
  |> List.find(x => x.name === planet)
  |> (
    result =>
      switch (result) {
      | planet => planet.distance
      | exception Not_found => 0
      }
  );
};