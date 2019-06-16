type payload = {
  planet_names: list(string),
  vehicle_names: list(string),
};
type payloadResult = {
  planet_name: option(string),
  status: string,
};

module Decode = {
  let payload = json =>
    Json.Decode.{
      planet_name: json |> field("planet_name", optional(string)),
      status: json |> field("status", string),
    };
};

module Encode = {
  open Json.Encode;

  let stringList = x =>
    x |> List.map(string) |> Array.of_list |> Json.Encode.jsonArray;

  let falconePayload = (token, payload) =>
    object_([
      ("token", string(token)),
      ("planet_names", stringList(payload.planet_names)),
      ("vehicle_names", stringList(payload.vehicle_names)),
    ]);
};

module Api = {
  let findFalcone = payload =>
    Js.Promise.(
      Auth.Api.fetchToken()
      |> then_((json: Auth.t) =>
           payload
           |> Encode.falconePayload(json.token)
           |> (
             data =>
               Http.post("https://findfalcone.herokuapp.com/find", data)
               |> then_(json => json |> Decode.payload |> resolve)
           )
         )
    );
};
/* Http.post("https://findfalcone.herokuapp.com/find") */