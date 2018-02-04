let empty: unit => array('elt);

let create: (int, 'elt) => array('elt);

let iteri: (array('elt), ~f: (int, 'elt) => unit) => unit;