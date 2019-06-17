type t = {
  vehicle: option(string),
  planet: string,
};

let updateCounter = (dict, key) => {
  let newCount = Belt.Option.getWithDefault(Js.Dict.get(dict, key), 0) + 1;
  Js.Dict.set(dict, key, newCount);
  Some(dict);
};

let vehiclesUsed = (missions, key) => {
  missions
  |> List.fold_left(
       (dict, mission) =>
         mission
         |> Belt.Option.flatMap(_, (mission: t) => mission.vehicle)
         |> Belt.Option.flatMap(_, updateCounter(dict))
         |> Belt.Option.getWithDefault(_, dict),
       Js.Dict.empty(),
     )
  |> Js.Dict.get(_, key)
  |> Belt.Option.getWithDefault(_, 0);
};