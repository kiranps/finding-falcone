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
      Http.get(Config.baseUrl ++ "/vehicles")
      |> then_(json => json |> Decode.vehicleList |> resolve)
    );
};

[@react.component]
let make = (~name, ~count, ~disable, ~selected, ~onClick) => {
  let className =
    "p-2 cursor-pointer text-sm border-b border-gray-500"
    ++ (
      disable ? "cursor-move pointer-events-none opacity-25" : "cursor-pointer"
    )
    ++ (selected ? " bg-teal-300 opacity-100 " : "");

  <div className onClick>
    <img
      className="h-6 w-6 m-auto inline-block"
      src={"/images/" ++ name ++ ".png"}
    />
    <span className="align-middle pl-1"> {React.string(name)} </span>
    <span className="align-middle">
      {React.string(" ( " ++ string_of_int(count) ++ " )")}
    </span>
  </div>;
};

let speed = (vehicleName, vehicles) =>
  vehicles
  |> List.find(x => x.name === vehicleName)
  |> (
    result =>
      switch (result) {
      | vehicle => Some(vehicle.speed)
      | exception Not_found => None
      }
  );