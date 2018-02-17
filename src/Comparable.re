module Result = {
  type t =
    | Same
    | Asc
    | Desc;
  let from = int =>
    if (int == 0) {
      Same;
    } else if (int > 0) {
      Asc;
    } else {
      Desc;
    };
};

module type S = {type t; let compare: (t, t) => Result.t;};