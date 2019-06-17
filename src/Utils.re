[@bs.val] external require: string => unit = "require";

let updateArray = (value, index, arr) => {
  arr[index] = value;
  arr;
};

let difference = (array, values) =>
  List.filter(elem => !List.mem(elem, values), array);

let qsGet = key =>
  ReasonReactRouter.dangerouslyGetInitialUrl().hash
  |> Js.String.split("?")
  |> Array.to_list
  |> (
    value =>
      switch (value) {
      | [_, query] => query
      | _ => ""
      }
  )
  |> QueryString.parseQueryString
  |> Js.Dict.get(_, key)
  |> (
    value =>
      switch (value) {
      | Some(Single(s)) => Some(s)
      | None => None
      }
  );