let length = String.length;

let get = (s, i) =>
  switch s.[i] {
  | exception (Invalid_argument(_)) => None
  | c => Some(c)
  };

let getExn = (s, i) =>
  switch (get(s, i)) {
  | Some(c) => c
  | None => failwith("index out of range")
  };

let compare = (s1, s2) =>
  Reason.String.compare(s1, s2) |> KanaeComparable.Result.from;

let iter = (s, ~f) => String.iter(f, s);

let iteri = (s, ~f) => String.iteri((i, elt) => f(~i, ~elt), s);

let isPrefix = (s, prefix) => {
  let rec f = (i, j, count) =>
    switch (get(s, i), get(prefix, j)) {
    | (Some(c1), Some(c2)) when c1 == c2 => f(i + 1, j + 1, count + 1)
    | _ => count
    };
  f(0, 0, 0) == length(prefix);
};

let isSuffix = (s, suffix) => {
  let rec f = (i, j, count) =>
    switch (get(s, i), get(suffix, j)) {
    | (Some(c1), Some(c2)) when c1 == c2 => f(i - 1, j - 1, count + 1)
    | _ => count
    };
  f(length(s) - 1, length(suffix) - 1, 0) == length(suffix);
};

let join = (~sep="", comps) => {
  let sepLen = length(sep);
  let len =
    List.fold_left((sum, comp) => sum + sepLen + length(comp), 0, comps);
  let compsLen = List.length(comps);
  let buf = Buffer.create(len);
  List.iteri(
    (i, comp) => {
      Buffer.add_string(buf, comp);
      if (i + 1 < compsLen) {
        Buffer.add_string(buf, sep);
      };
    },
    comps
  );
  Buffer.contents(buf);
};

module Key = {
  type t = string;
  let compare = compare;
};

module Map = KanaeMap.Make(Key);