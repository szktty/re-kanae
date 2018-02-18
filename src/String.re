open Import;

module S = RE.String;

type t = string;

let length = S.length;

let get = (s, i) =>
  switch (S.get(s, i)) {
  | exception (Invalid_argument(_)) => None
  | c => Some(c)
  };

let getExn = (s, i) =>
  switch (get(s, i)) {
  | Some(c) => c
  | None => failwith("index out of range")
  };

let compare = (s1, s2) => S.compare(s1, s2) |> Comparable.Result.from;

let each = (s, ~f) => S.iter(f, s);

let eachi = (s, ~f) => S.iteri((i, elt) => f(~i, ~elt), s);

let map = (s, ~f) => S.map(f, s);

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
  let bytes = RE.Bytes.create(List.length(cs));
  RE.List.iteri((i, c) => RE.Bytes.set(bytes, i, c), cs);
  RE.Bytes.to_string(bytes);
};

let join = (~sep="", comps) => {
  let sepLen = length(sep);
  let len =
    RE.List.fold_left((sum, comp) => sum + sepLen + length(comp), 0, comps);
  let compsLen = RE.List.length(comps);
  let buf = RE.Buffer.create(len);
  RE.List.iteri(
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
  each(s, ~f=c => accu0 := f(~accu=accu0^, ~elt=c));
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
  RE.List.rev([fromCharList(last), ...accu]);
};

include
  JSONable.Make(
    {
      type t = string;
      let fromJSON = (json: BS.Js.Json.t) => BS.Js.Json.decodeString(json);
      let toJSON = BS.Js.Json.string;
    }
  );

module Key = {
  type t = string;
  let compare = compare;
};

module Map = Map.Make(Key);