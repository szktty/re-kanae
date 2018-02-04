module A = Reason.Array;

let empty = () => [||];

let create = A.make;

let iteri = (ary, ~f) => A.iteri(f, ary);