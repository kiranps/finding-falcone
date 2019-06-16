type t = {token: string};

module Decode = {
  let token = json => Json.Decode.{token: json |> field("token", string)};
};

module Api = {
  let fetchToken = () =>
    Js.Promise.(
      Http.post("https://findfalcone.herokuapp.com/token", Js.Json.null)
      |> then_(json => json |> Decode.token |> resolve)
    );
};