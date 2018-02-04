let length: string => int;

let get: (string, int) => option(char);

let getExn: (string, int) => char;

let iter: (string, ~f: char => unit) => unit;

let iteri: (string, ~f: (int, char) => unit) => unit;

let isPrefix: (string, string) => bool;

let isSuffix: (string, string) => bool;

let join: (~sep: string=?, list(string)) => string;