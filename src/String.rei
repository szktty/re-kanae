type t = string;

let fromCharList: list(char) => string;

let length: string => int;

let get: (string, int) => option(char);

let getExn: (string, int) => char;

let each: (string, ~f: char => unit) => unit;

let eachi: (string, ~f: (~i: int, ~elt: char) => unit) => unit;

let map: (string, ~f: char => char) => string;

let reduce:
  (string, ~init: 'accu, ~f: (~accu: 'accu, ~elt: char) => 'accu) => 'accu;

let isPrefix: (string, string) => bool;

let isSuffix: (string, string) => bool;

let join: (~sep: string=?, list(string)) => string;

let split: (string, ~on: char) => list(string);

include JSONable.S with type t := t;

module Map: Map.S with type key := string;