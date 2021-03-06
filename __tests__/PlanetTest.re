open Jest;
open Planet;

let planets = [
  {name: "Donlon", distance: 100},
  {name: "Enchai", distance: 200},
  {name: "Jebing", distance: 300},
  {name: "Sapir", distance: 400},
  {name: "Lerbin", distance: 500},
  {name: "Pingasor", distance: 600},
];

let planetsRaw: string = {|
    [
     {"name": "Donlon", "distance": 100},
     {"name": "Enchai", "distance": 200},
     {"name": "Jebing", "distance": 300},
     {"name": "Sapir", "distance": 400},
     {"name": "Lerbin", "distance": 500},
     {"name": "Pingasor", "distance": 600}
    ]
  |};

describe("Planet", () => {
  open Expect;

  test("find distance to Donlon", () =>
    planets |> distance("Donlon") |> expect |> toBe(100)
  );

  test("decodes planets json string into reasonlist", () =>
    planetsRaw
    |> Js.Json.parseExn
    |> Decode.planetList
    |> expect
    |> toEqual(planets)
  );
});