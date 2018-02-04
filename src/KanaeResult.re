type t('ok, 'error) =
  | OK('ok)
  | Error('error);

let fromOpt = (ok, ~error) =>
  switch ok {
  | Some(value) => OK(value)
  | None => Error(error)
  };

let isOK = res =>
  switch res {
  | OK(_) => true
  | Error(_) => false
  };

let isError = res =>
  switch res {
  | OK(_) => false
  | Error(_) => true
  };

let ok = res =>
  switch res {
  | OK(value) => Some(value)
  | Error(_) => None
  };

let error = res =>
  switch res {
  | Error(value) => Some(value)
  | OK(_) => None
  };

let iter = (res, ~f: 'ok => unit) : unit =>
  switch res {
  | OK(value) => f(value)
  | Error(_) => ()
  };

let iterError = (res, ~f: 'error => unit) : unit =>
  switch res {
  | Error(value) => f(value)
  | OK(_) => ()
  };

let map = (res, ~f: 'ok => 'c) : t('c, 'error) =>
  switch res {
  | OK(value) => OK(f(value))
  | Error(value) => Error(value)
  };

let mapError = (res, ~f: 'error => 'c) : t('ok, 'c) =>
  switch res {
  | Error(value) => Error(f(value))
  | OK(value) => OK(value)
  };