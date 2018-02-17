open Builtin;

let length = Reason.List.length;

let iteri = (list, ~f) => {
  let rec iter = (i, list) =>
    switch list {
    | [] => ()
    | [hd, ...tl] =>
      f(~i, ~elt=hd);
      iter(i + 1, tl);
    };
  iter(0, list);
};

let map = (list, ~f) => Reason.List.map(f, list);

let reduce = (list, ~init, ~f) =>
  Reason.List.fold_left((accu, elt) => f(~accu, ~elt), init, list);

let contains = (list, ~f) => Reason.List.exists(f, list);

let toArray = list =>
  switch list {
  | [] => [||]
  | [hd, ..._tl] =>
    let array = Reason.Array.make(length(list), hd);
    iteri(list, ~f=(~i, ~elt) => array[i] = elt);
    array;
  };