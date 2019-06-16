[@react.component]
let make = _ => {
  <div>
    <span> {"Header" |> React.string} </span>
    <a href="#/home"> {React.string("home")} </a>
  </div>;
};