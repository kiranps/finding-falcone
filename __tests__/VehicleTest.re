open Jest;
open Vehicle;
let vehicles = [
  {name: "Space pod", total_no: 2, max_distance: 200, speed: 2},
  {name: "Space rocket", total_no: 1, max_distance: 300, speed: 4},
  {name: "Space shuttle", total_no: 1, max_distance: 400, speed: 5},
  {name: "Space ship", total_no: 2, max_distance: 600, speed: 10},
];

let vehicleRaw: string = {|
     [
      {"name": "Space pod", "total_no": 2, "max_distance": 200, "speed": 2},
      {"name": "Space rocket", "total_no": 1, "max_distance": 300, "speed": 4},
      {"name": "Space shuttle", "total_no": 1, "max_distance": 400, "speed": 5},
      {"name": "Space ship", "total_no": 2, "max_distance": 600, "speed": 10}
     ]
  |};

describe("Vehicle", () => {
  open Expect;

  test("find speed of Space pod", () =>
    vehicles |> speed("Space pod") |> expect |> toBe(Some(2))
  );

  test("decodes planets json string into reasonlist", () =>
    vehicleRaw
    |> Js.Json.parseExn
    |> Decode.vehicleList
    |> expect
    |> toEqual(vehicles)
  );
});