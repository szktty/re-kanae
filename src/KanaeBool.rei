let if_: (bool, ~f: unit => unit) => unit;

let optIf_: (bool, ~f: unit => 'value) => option('value);