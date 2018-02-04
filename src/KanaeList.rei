let length: list('elt) => int;

let iteri: (list('elt), ~f: (int, 'elt) => unit) => unit;

let map: (list('elt1), ~f: 'elt1 => 'elt2) => list('elt2);

let reduce: (list('elt), ~init: 'accu, ~f: ('accu, 'elt) => 'accu) => 'accu;

let contains: (list('elt), ~f: 'elt => bool) => bool;

let toArray: list('elt) => array('elt);