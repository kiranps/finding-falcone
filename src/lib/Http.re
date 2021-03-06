let get = url => Js.Promise.(Fetch.fetch(url) |> then_(Fetch.Response.json));

let post = (url, data) => {
  let contentType = [("Content-Type", "application/json")];
  let accept = [("Accept", "application/json")];
  let method_ = Fetch.Post;
  let headers =
    contentType
    |> List.append(accept)
    |> Array.of_list
    |> Fetch.HeadersInit.makeWithArray;
  let body = data |> Js.Json.stringify |> Fetch.BodyInit.make;

  Js.Promise.(
    Fetch.fetchWithInit(
      url,
      Fetch.RequestInit.make(~method_, ~body, ~headers, ()),
    )
    |> then_(Fetch.Response.json)
  );
};