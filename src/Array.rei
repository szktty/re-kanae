let empty: unit => array('elt);

let create: (int, 'elt) => array('elt);

let get: (array('elt), int) => option('elt);

let getExn: (array('elt), int) => 'elt;

let set: (array('elt), int, 'elt) => unit;

let eachi: (array('elt), ~f: (~i: int, ~elt: 'elt) => unit) => unit;