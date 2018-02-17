open Import;

module type S = {
  type t;
  let fromJSON: BS.Js.Json.t => option(t);
  let toJSON: t => BS.Js.Json.t;
};

module Make = (Item: S) : (S with type t := Item.t) => {
  type t = Item.t;
  let fromJSON = Item.fromJSON;
  let toJSON = Item.toJSON;
};