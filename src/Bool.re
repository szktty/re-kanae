let if_ = (flag, ~f) =>
  if (flag) {
    f();
  };

let optIf = (flag, ~f) =>
  if (flag) {
    Some(f());
  } else {
    None;
  };