module type S = {
  type elt;
  type t;
  let length: t => int;
  let get: (t, ~i: int) => option(elt);
  let getExn: (t, ~i: int) => elt;
  let first: t => option(elt);
  let last: t => option(elt);
  let equal: (t, t, ~f: (~a: elt, ~b: elt) => bool) => bool;
  let each: (t, ~f: (~elt: elt) => unit) => unit;
  let eachi: (t, ~f: (~i: int, ~elt: elt) => unit) => unit;
  let map: (t, ~f: (~elt: elt) => 'elt1) => t;
  let mapi: (t, ~f: (~i: int, ~elt: elt) => 'elt1) => t;
  let revMap: (t, ~f: (~elt: elt) => 'elt1) => t;
  let revMapi: (t, ~f: (~i: int, ~elt: elt) => 'elt1) => t;
  let reduce:
    (t, ~init: 'accu, ~f: (~accu: 'accu, ~elt: elt) => 'accu) => 'accu;
  let reducei:
    (t, ~init: 'accu, ~f: (~accu: 'accu, ~i: int, ~elt: elt) => 'accu) => 'accu;
  let revReduce:
    (t, ~init: 'accu, ~f: (~accu: 'accu, ~elt: elt) => 'accu) => 'accu;
  let revReducei:
    (t, ~init: 'accu, ~f: (~accu: 'accu, ~i: int, ~elt: elt) => 'accu) => 'accu;
  let reduceRight:
    (t, ~init: 'accu, ~f: (~accu: 'accu, ~elt: elt) => 'accu) => 'accu;
  let reduceiRight:
    (t, ~init: 'accu, ~f: (~accu: 'accu, ~i: int, ~elt: elt) => 'accu) => 'accu;
  let includes: (t, ~f: (~elt: elt) => bool) => bool;
  let includesi: (t, ~f: (~i: int, ~elt: elt) => bool) => bool;
  let all: (t, ~f: (~i: int, ~elt: elt) => bool) => bool;
  let any: (t, ~f: (~i: int, ~elt: elt) => bool) => bool;
  let find: (t, ~f: (~elt: elt) => bool) => option(elt);
  let findi: (t, ~f: (~i: int, ~elt: elt) => bool) => option(elt);
  let findExn: (t, ~f: (~elt: elt) => bool) => elt;
  let findiExn: (t, ~f: (~i: int, ~elt: elt) => bool) => elt;
  let findAll: (t, ~f: (~elt: elt) => bool) => list(elt);
  let filter: (t, ~f: (~elt: elt) => bool) => t;
  let partition: (t, ~f: (~elt: elt) => bool) => (t, t);
  let rev: t => t;
  let concat: (t, t) => t;
  let revConcat: (t, t) => t;
  let sort: (t, ~f: (elt, elt) => Comparable.Result.t) => t;
  let stableSort: (t, ~f: (elt, elt) => Comparable.Result.t) => t;
  let fastSort: (t, ~f: (elt, elt) => Comparable.Result.t) => t;
};

module type Item = {
  type elt;
  type t;
  let length: t => int;
  let get: (t, ~i: int) => option('elt);
  let each: (t, ~f: (~elt: 'elt) => unit) => unit;
  let includes: (t, ~f: (~elt: elt) => bool) => bool;
};
/*module Make = (Item: Item) : S => {};*/