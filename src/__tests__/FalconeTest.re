open Jest;
open Falcone;

describe("Falcone", () => {
  open Expect;

  let token = "ulqxJnjaxTPIBVSfcYaqRJBhhUOBwIsd";

  let falconePayload = {
    planet_names: ["Sapir", "Lerbin", "Enchai", "Jebing"],
    vehicle_names: [
      "Space shuttle",
      "Space ship",
      "Space rocket",
      "Space ship",
    ],
  };

  let responsePayload = {planet_name: Some("Sapir"), status: "success"};

  let responsePayloadRaw = {|
    {
      "planet_name":"Sapir",
      "status":"success"
    }
  |};

  let falconePayloadRaw = {|{"token":"ulqxJnjaxTPIBVSfcYaqRJBhhUOBwIsd","planet_names":["Sapir","Lerbin","Enchai","Jebing"],"vehicle_names":["Space shuttle","Space ship","Space rocket","Space ship"]}|};

  test("encode falcone payload", () =>
    falconePayload
    |> Falcone.Encode.falconePayload(token)
    |> Json.stringify
    |> expect
    |> toEqual(falconePayloadRaw)
  );

  test("decodes falcone response payload", () =>
    responsePayloadRaw
    |> Js.Json.parseExn
    |> Decode.payload
    |> expect
    |> toEqual(responsePayload)
  );
});