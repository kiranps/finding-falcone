[@bs.val] external require: string => unit = "require";
let window = [%bs.raw {| window |}];

[@bs.send]
external addEvent: (Dom.window, string, unit => unit) => unit =
  "addEventListener";

[@bs.send]
external removeEvent: (Dom.window, string, unit => unit) => unit = "";