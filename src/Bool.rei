let if_: (bool, ~f: unit => unit) => unit;

let optIf: (bool, ~f: unit => 'value) => option('value);