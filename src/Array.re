open Import;

let empty = () => [||];

let create = RE.Array.make;

let getExn = RE.Array.get;

let get = (ary, i) =>
  switch (getExn(ary, i)) {
  | exception (Invalid_argument(_)) => None
  | elt => Some(elt)
  };

let set = RE.Array.set;

let iteri = (ary, ~f) => RE.Array.iteri((i, elt) => f(~i, ~elt), ary);