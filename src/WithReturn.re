type return('a) = {return: 'b .'a => 'b};

let withReturn = (type value, f) => {
  module M = {
    exception Return(value);
  };
  let is_alive = ref(true);
  let return = value => {
    if (! is_alive^) {
      failwith("use of [return] from a [with_return] that already returned");
    };
    raise(M.Return(value));
  };
  try {
    let value = f({return: return});
    is_alive := false;
    value;
  } {
  | exn =>
    is_alive := false;
    switch exn {
    | M.Return(value) => value
    | _ => raise(exn)
    };
  };
};