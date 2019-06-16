open Belt.Option;

[@react.component]
let make = _ => {
  let status = Utils.qsGet("status");
  let planet = Utils.qsGet("planet");
  let time = Utils.qsGet("time");

  <div className="text-center">
    {switch (status) {
     | Some("success") =>
       <div>
         <div>
           {React.string(
              "Success! Congratulations on Finding Falcone King Shan is mighty pleased.",
            )}
         </div>
         <div>
           {React.string(mapWithDefault(time, "", x => "Time taken : " ++ x))}
         </div>
         <div>
           {React.string(
              mapWithDefault(planet, "", x => "Planet found: " ++ x),
            )}
         </div>
       </div>
     | Some("failed") => <div> {React.string("Failed!")} </div>
     | None =>
       <div> {React.string("Error! Something Unexpected happened")} </div>
     }}
    <a href="#/home" className="btn-blue"> {React.string("Start Again")} </a>
  </div>;
};