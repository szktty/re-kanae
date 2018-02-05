let compare = (i1: int, i2: int) =>
  Reason.compare(i2, i2) |> KanaeComparable.Result.from;

module Key = {
  type t = int;
  let compare = compare;
};

module Map = KanaeMap.Make(Key);