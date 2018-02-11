type t = string;

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

let map = (s, ~f) => String.map(f, s);

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

let fromCharList = (cs: list(char)) : string => {
  let bytes = Bytes.create(List.length(cs));
  List.iteri((i, c) => Bytes.set(bytes, i, c), cs);
  Bytes.to_string(bytes);
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

let reduce = (s, ~init, ~f) => {
  let accu0 = ref(init);
  iter(s, ~f=c => accu0 := f(~accu=accu0^, ~elt=c));
  accu0^;
};

let split = (s, ~on: char) : list(string) => {
  let (last, accu) =
    reduce(
      s,
      ~init=([], []),
      ~f=(~accu as (last: list(char), accu), ~elt as c: char) =>
      if (c == on) {
        ([], [fromCharList(last), ...accu]);
      } else {
        ([c, ...last], accu);
      }
    );
  List.rev([fromCharList(last), ...accu]);
};

include
  KanaeJSONable.Make(
    {
      type t = string;
      let fromJSON = (json: Js.Json.t) => Js.Json.decodeString(json);
      let toJSON = Js.Json.string;
    }
  );

module Key = {
  type t = string;
  let compare = compare;
};

module Map = KanaeMap.Make(Key);