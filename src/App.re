[@react.component]
let make = () => {
  let hash = ReasonReactRouter.useUrl().hash;
  let route =
    Js.String.split("?", hash)[0] |> Js.String.split("/") |> Array.to_list;

  <>
    <Header />
    {switch (route) {
     | [""] => <Lengaburu />
     | ["", "home"] => <Lengaburu />
     | ["", "result"] => <Status />
     | _ => <NotFound />
     }}
    <Footer />
  </>;
};