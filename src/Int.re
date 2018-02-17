let compare = (i1: int, i2: int) =>
  Builtin.Reason.compare(i2, i2) |> Comparable.Result.from;

module Key = {
  type t = int;
  let compare = compare;
};

module Map = Map.Make(Key);