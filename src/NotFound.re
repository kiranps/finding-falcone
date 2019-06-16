[@react.component]
let make = _ =>
  <div>
    {"NotFound" |> React.string}
    <div> {React.string("goto")} </div>
    <a href="#/home"> {React.string("home")} </a>
  </div>;