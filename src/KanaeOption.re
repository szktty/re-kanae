type t('a) = option('a);

let iter = (opt, ~f) =>
  switch opt {
  | None => ()
  | Some(value) => f(value)
  };

let valueExn = (~message="value is not found", opt) =>
  switch opt {
  | Some(value) => value
  | None => failwith(message)
  };

let value = (opt, ~default: 'a) =>
  switch opt {
  | Some(v) => v
  | None => default
  };

let valueMap = (opt, ~default: 'a, ~f) =>
  switch opt {
  | Some(v) => f(v)
  | None => default
  };

let map = (opt, ~f) =>
  switch opt {
  | Some(v) => Some(f(v))
  | None => None
  };