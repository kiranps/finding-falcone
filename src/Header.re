[@react.component]
let make = _ => {
  <nav
    className="fixed flex w-full h-12 bg-white border-b border-gray-200 p-3 z-10 justify-between">
    <span> {"Finding Falcone" |> React.string} </span>
    <a href="#/home" className="text-blue-500 hover:text-blue-800">
      {React.string("home")}
    </a>
  </nav>;
};