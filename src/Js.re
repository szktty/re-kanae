open Builtin;

module J = BuckleScript.Js;

module Json = BuckleScript.Js.Json;

type t('a) = J.t('a);

type boolean = J.boolean;

type null('a) = J.null('a);

type undefined('a) = J.undefined('a);

type nullable('a) = J.nullable('a);

type type_ =
  | Null
  | Undefined
  | Boolean
  | Number
  | String
  | Array
  | Object
  | Function;

let typeName = J.typeof;

let type_ = (js: t('a)) : type_ =>
  switch (typeName(js)) {
  | "undefined" => Undefined
  | "boolean" => Boolean
  | "number" => Number
  | "string" => String
  | "function" => Function
  | "object" =>
    if (J.unsafe_le(Reason.Obj.magic(js), 0)) {
      Null;
    } else if (J.Array.isArray(js)) {
      Array;
    } else {
      Object;
    }
  | _ => failwith("unknown type")
  };

let fromBool = J.Boolean.to_js_boolean;

let fromList = List.toArray;

let fromOpt = J.Null.fromOption;

let fromOptMap = (opt, ~f) => Option.map(opt, ~f) |> J.Null.fromOption;

let toBool = J.to_bool;

let toOpt = J.toOption;

let log = J.log;

let diet = (js: t('a)) : t('a) => {
  let rec diet0 = (js: t('a)) =>
    switch (type_(js)) {
    | Object =>
      let dict: J.Dict.t(t('a)) = Reason.Obj.magic(js);
      let newDict = J.Dict.empty();
      Reason.Array.iter(
        key => {
          let value = J.Dict.unsafeGet(dict, key);
          switch (type_(value)) {
          | Null => ()
          | _ => J.Dict.set(newDict, key, diet0(Reason.Obj.magic(value)))
          };
        },
        J.Dict.keys(dict)
      );
      Reason.Obj.magic(newDict);
    | _ => js
    };
  diet0(js);
};

module False = {
  type t('a);
  let from = (opt: option('a)) : t('a) =>
    switch opt {
    | None => Reason.Obj.magic(J.false_)
    | Some(value) => Reason.Obj.magic(value)
    };
  let to_ = (opt: t('a)) : option('a) =>
    if (Reason.Obj.magic(opt) === J.false_) {
      None;
    } else {
      Some(Reason.Obj.magic(opt));
    };
  let some = value => from(Some(value));
  let none = () => from(None);
};

module Any = {
  type t = BuckleScript.Js.t(unit);
  let return = (value: 'a) : t => Reason.Obj.magic(value);
  let string = (value: t) : option(string) =>
    switch (type_(value)) {
    | String => Some(Reason.Obj.magic(value))
    | _ => None
    };
};

module Iterator = {
  type t('value);
  type elt('value);
  module Basic = {
    [@bs.send] external next : t('value) => elt('value) = "next";
    [@bs.get] external isDone : elt('value) => boolean = "done";
    [@bs.get] external value : elt('value) => 'value = "value";
  };
  let next = iter : option('value) => {
    let elt = Basic.next(iter);
    Basic.isDone(elt) |> J.to_bool ? None : Some(Basic.value(elt));
  };
  let iter = (iter: t('value), ~f: 'value => unit) : unit => {
    let rec iter0 = () =>
      switch (next(iter)) {
      | None => ()
      | Some(value) =>
        f(value);
        iter0();
      };
    iter0();
  };
};