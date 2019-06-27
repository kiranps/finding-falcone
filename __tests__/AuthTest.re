open Jest;
open Auth;

describe("Auth", () => {
  open Expect;

  let tokenRaw: string = {|
     {"token": "1234"}
  |};

  test("decodes token", () =>
    tokenRaw
    |> Js.Json.parseExn
    |> Decode.token
    |> expect
    |> toEqual({token: "1234"})
  );
});