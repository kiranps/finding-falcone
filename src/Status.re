open Belt.Option;

[@react.component]
let make = _ => {
  let status = Utils.qsGet("status");
  let planet = Utils.qsGet("planet");
  let time = Utils.qsGet("time");

  <div className="flex min-h-screen justify-center">
    <div
      className="flex flex-col self-center pt-12 pb-12 justify-center items-center">
      {switch (status) {
       | Some("success") =>
         <div className="text-center">
           <div className="mt-2">
             {React.string(
                "Success! Congratulations on Finding Falcone King Shan is mighty pleased.",
              )}
           </div>
           <div className="mt-2">
             {React.string(
                mapWithDefault(time, "", x => "Time taken : " ++ x),
              )}
           </div>
           <div className="mt-2">
             {React.string(
                mapWithDefault(planet, "", x => "Planet found: " ++ x),
              )}
           </div>
         </div>
       | Some("failed") =>
         <div>
           {React.string("Failed! King Shan will send you to his coal mine")}
         </div>
       | _ =>
         <div className="mt-2">
           {React.string("Failed! Something Unexpected happened! Try Again")}
         </div>
       }}
      <a href="#/home" className="btn-blue mt-4">
        {React.string("Start Again")}
      </a>
    </div>
  </div>;
};