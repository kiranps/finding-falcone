type t = {token: string};

module Decode = {
  let token = json => Json.Decode.{token: json |> field("token", string)};
};

module Api = {
  let fetchToken = () =>
    Js.Promise.(
      Http.post(Config.Api.baseUrl ++ "/token", Js.Json.null)
      |> then_(json => json |> Decode.token |> resolve)
    );
};