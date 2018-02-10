module A = Reason.Array;

let empty = () => [||];

let create = A.make;

let getExn = A.get;

let get = (ary, i) =>
  switch (getExn(ary, i)) {
  | exception (Invalid_argument(_)) => None
  | elt => Some(elt)
  };

let iteri = (ary, ~f) => A.iteri((i, elt) => f(~i, ~elt), ary);