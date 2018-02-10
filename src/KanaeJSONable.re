module type S = {
  type t;
  let fromJSON: Js.Json.t => option(t);
  let toJSON: t => Js.Json.t;
};

module Make = (Item: S) : (S with type t := Item.t) => {
  type t = Item.t;
  let fromJSON = Item.fromJSON;
  let toJSON = Item.toJSON;
};