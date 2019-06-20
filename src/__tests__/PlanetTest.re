open Jest;
open Planet;

let logger: 'a => 'a =
  value => {
    Js.log(value);
    value;
  };

describe("Planet", () => {
  open Expect;

  let planets = [
    {name: "Donlon", distance: 100},
    {name: "Enchai", distance: 200},
    {name: "Jebing", distance: 300},
    {name: "Sapir", distance: 400},
    {name: "Lerbin", distance: 500},
    {name: "Pingasor", distance: 600},
  ];

  let planetsJson = [
    {name: "Donlon", distance: 100},
    {name: "Enchai", distance: 200},
    {name: "Jebing", distance: 300},
  ];

  let planetsRaw: string = {|
    [
     {"name": "Donlon", "distance": 100},
     {"name": "Enchai", "distance": 200},
     {"name": "Jebing", "distance": 300}
    ]
  |};

  test("find distance to Donlon", () =>
    planets |> distance("Donlon") |> expect |> toBe(100)
  );

  test("array", () =>
    List.map(x => x * x, [1, 2, 3]) |> expect |> toEqual([1, 4, 9])
  );

  test("decodes planet", () =>
    planetsRaw
    |> Js.Json.parseExn
    |> Decode.planetList
    |> expect
    |> toEqual(planetsJson)
  );
});