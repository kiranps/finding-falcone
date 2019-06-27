open Jest;
open QueryString;

let query = "status=success&planet=Jebing&time=265";

describe("QueryString", () => {
  open Expect;

  test("get status from query string", () =>
    query
    |> parseQueryString
    |> Js.Dict.get(_, "status")
    |> (
      fun
      | Some(Single(s)) => s
      | _ => ""
    )
    |> expect
    |> toBe("success")
  );

  test("get time from query string", () =>
    query
    |> parseQueryString
    |> Js.Dict.get(_, "time")
    |> (
      fun
      | Some(Single(s)) => s
      | _ => ""
    )
    |> expect
    |> toBe("265")
  );
});