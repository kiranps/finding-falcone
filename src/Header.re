[@react.component]
let make = _ => {
  <nav className="flex items-center justify-between flex-wrap bg-teal-500 p-3">
    <span> {"Header" |> React.string} </span>
    <a href="#/home"> {React.string("home")} </a>
  </nav>;
};