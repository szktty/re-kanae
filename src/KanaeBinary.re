/* Buffer */
module Basic = {
  type class_;
  type t;
  [@bs.val] external buffer : class_ = "Buffer";
  [@bs.send] external alloc : (class_, int) => t = "alloc";
  [@bs.send] external length : t => int = "length";
};

type t = Basic.t;

/*let fromArray = Basic.fromArray;*/
let alloc = len => Basic.alloc(Basic.buffer, len);

let length = Basic.length;