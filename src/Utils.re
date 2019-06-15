[@bs.val] external require: string => unit = "require";

let difference = (array, values) =>
  List.filter(elem => !List.mem(elem, values), array);