open Jest;
open Mission;

describe("Mission", () => {
  open Expect;

  let missions1 = [
    Some({planet: "Enchai", vehicle: Some("Space pod")}),
    Some({planet: "Donlon", vehicle: Some("Space pod")}),
    Some({planet: "Sapir", vehicle: Some("Space ship")}),
    None,
  ];

  let missions2 = [
    Some({planet: "Enchai", vehicle: Some("Space pod")}),
    Some({planet: "Donlon", vehicle: Some("Space pod")}),
    Some({planet: "Sapir", vehicle: Some("Space ship")}),
    Some({planet: "Lerbin", vehicle: Some("Space ship")}),
  ];

  test("update count of Space Pod by 1", () => {
    let dict = Js.Dict.empty();
    Js.Dict.set(dict, "Space Pod", 0);
    Js.Dict.set(dict, "Space Rocket", 0);

    let _ = Mission.updateCounter(dict, "Space Pod");

    switch (Js.Dict.get(dict, "Space Pod")) {
    | Some(dict) => dict |> expect |> toBe(1)
    | None => true |> expect |> ExpectJs.toBeTruthy
    };
  });

  test("number of Space Pods used must be 2", () =>
    Mission.vehiclesUsed(missions1, "Space pod") |> expect |> toBe(2)
  );

  test("number of Space Ships used must be 1", () =>
    Mission.vehiclesUsed(missions1, "Space ship") |> expect |> toBe(1)
  );

  test("missions1 should not be ready to launch", () =>
    Mission.isReadyToLaunch(missions1) |> expect |> ExpectJs.toBeFalsy
  );

  test("missions2 be ready to launch", () =>
    Mission.isReadyToLaunch(missions1) |> expect |> ExpectJs.toBeFalsy
  );

  test("missions2 be ready to launch", () =>
    Mission.isReadyToLaunch(missions2) |> expect |> ExpectJs.toBeTruthy
  );

  test("total time taken for the mission should be 240", () =>
    Mission.totalTimeTaken(
      missions2,
      VehicleTest.vehicles,
      PlanetTest.planets,
    )
    |> expect
    |> toBe(240)
  );
});