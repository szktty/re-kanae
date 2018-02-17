type t = Js.Json.t;

let fromString = Js.Json.string;

let fromStringList = list => Js.Json.stringArray(KanaeList.toArray(list));

let parseExn = Js.Json.parseExn;

let parse = s =>
  try (Some(parseExn(s))) {
  | _ => None
  };
