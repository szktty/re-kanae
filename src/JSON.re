open Import;

type t = BS.Js.Json.t;

let fromString = BS.Js.Json.string;

let fromStringList = list => BS.Js.Json.stringArray(List.toArray(list));

let parseExn = BS.Js.Json.parseExn;

let parse = s =>
  try (Some(parseExn(s))) {
  | _ => None
  };