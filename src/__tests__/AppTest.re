open Jest;
open Expect;
open ReactTestingLibrary;

[@bs.get] external firstChild: Dom.element => Dom.element = "";
[@bs.get] external innerHTML: Dom.element => string = "";

Jest.useFakeTimers();

test("Select works", () =>
  <Select values=["one", "two", "three"] onChange={_ => ()} />
  |> render
  |> container
  |> expect
  |> toMatchSnapshot
);

/* test("Select simulate click", () => {
     let spy = JestJs.inferred_fn();
     let fn = spy |> MockJs.fn;
     let handleChange = _ => fn(. "clicked!") |> ignore;

     let select =
       <Select values=["one", "two", "three"] onChange=handleChange />
       |> render
       |> container;

     let _ = select |> firstChild |> firstChild |> FireEvent.click;

     Jest.advanceTimersByTime(2500);

     expect(spy |> MockJs.calls) |> toEqual([|"clicked!"|]);
   }); */