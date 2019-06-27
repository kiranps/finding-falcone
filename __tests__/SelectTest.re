open Jest;
open Expect;
open ReactTestingLibrary;

[@bs.get] external firstChild: Dom.element => Dom.element = "";
[@bs.get] external innerHTML: Dom.element => string = "";

test("Select works", () =>
  <Select values=["one", "two", "three"] onChange={_ => ()} />
  |> render
  |> container
  |> expect
  |> toMatchSnapshot
);