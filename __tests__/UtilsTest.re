open Jest;
open Utils;

let query = "status=success&planet=Jebing&time=265";

describe("Utils", () => {
  open Expect;

  test("find difference of two list", () =>
    [1, 2, 3] |> difference([3, 2, 4]) |> expect |> toEqual([4])
  );

  test("update item in an array", () =>
    5
    |> updateArray(_, 2, [|1, 2, 3, 4|])
    |> expect
    |> toEqual([|1, 2, 5, 4|])
  );
});