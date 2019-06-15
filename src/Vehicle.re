type t = {
  max_distance: int,
  name: string,
  speed: int,
  total_no: int,
};

module Decode = {
  let vehicle = json =>
    Json.Decode.{
      max_distance: json |> field("max_distance", int),
      name: json |> field("name", string),
      speed: json |> field("speed", int),
      total_no: json |> field("total_no", int),
    };

  let vehicleList = vehicle |> Json.Decode.list;
};

module Api = {
  let fetchVehicles = () =>
    Js.Promise.(
      Http.get("/vehicles")
      |> then_(json => json |> Decode.vehicleList |> resolve)
    );
};

[@react.component]
let make = (~name, ~count, ~active, ~onClick) =>
  <div className="cursor-pointer" onClick>
    <Icon.Radio active />
    <span> {React.string(name)} </span>
    <span> {React.string(" ( " ++ count ++ " )")} </span>
  </div>;