include Js;

type any = t(unit);

module Falseable = {
  type t('a);
  let from = (opt: option('a)) : t('a) =>
    switch opt {
    | None => Reason.Obj.magic(Js.false_)
    | Some(value) => Reason.Obj.magic(value)
    };
  let to_ = (opt: t('a)) : option('a) =>
    if (Reason.Obj.magic(opt) === Js.false_) {
      None;
    } else {
      Some(Reason.Obj.magic(opt));
    };
};

module Any = {
  type t = any;
  type type_ =
    | Null
    | Undefined
    | Boolean
    | Number
    | String
    | Array
    | Object
    | Function;
  let type_ = (js: Js.t('a)) : type_ =>
    switch (Js.typeof(js)) {
    | "undefined" => Undefined
    | "boolean" => Boolean
    | "number" => Number
    | "string" => String
    | "function" => Function
    | "object" =>
      if (Js.unsafe_le(Reason.Obj.magic(js), 0)) {
        Null;
      } else if (Js.Array.isArray(js)) {
        Array;
      } else {
        Object;
      }
    | _ => failwith("unknown type")
    };
  let fromString = (value: string) : t => Reason.Obj.magic(value); /* TODO */
  let toString = (value: t) : string => Reason.Obj.magic(value);
  let toStringOrNull = (value: t) : option(string) => Reason.Obj.magic(value);
  /* TODO: iter, map */
  let diet = (js: Js.t('a)) : Js.t('a) => {
    let rec diet0 = (js: Js.t('a)) =>
      switch (type_(js)) {
      | Object =>
        let dict: Js.Dict.t(Js.t('a)) = Reason.Obj.magic(js);
        let newDict = Js.Dict.empty();
        Reason.Array.iter(
          key => {
            let value = Js.Dict.unsafeGet(dict, key);
            switch (type_(value)) {
            | Null => ()
            | _ => Js.Dict.set(newDict, key, diet0(Reason.Obj.magic(value)))
            };
          },
          Js.Dict.keys(dict)
        );
        Reason.Obj.magic(newDict);
      | _ => js
      };
    diet0(js);
  };
};

module Primitive = {
  type t =
    | Null
    | Undefined
    | Boolean
    | Number
    | String
    | Array
    | Object
    | Function;
  let type_ = (js: Js.t('a)) : t => {
    let name = Js.typeof(js);
    switch name {
    | "undefined" => Undefined
    | "boolean" => Boolean
    | "number" => Number
    | "string" => String
    | "function" => Function
    | "object" =>
      /* null check */
      if (Js.Array.isArray(name)) {
        Array;
      } else if (Js.unsafe_le(Reason.Obj.magic(js), 0)) {
        Null;
      } else {
        Object;
      }
    | _ => failwith("unknown type")
    };
  };
  let isNull = js => type_(js) == Null;
  let isUndefined = js => type_(js) == Undefined;
  let isEmpty = js =>
    switch (type_(js)) {
    | Null
    | Undefined => true
    | _ => false
    };
  let isZero = js => Reason.Obj.magic(js) === 0;
  /* danger */
  let diet = (~ignore: list(string)=[], js: Js.t('a)) : Js.t('a) => {
    let ignore = KanaeList.map(ignore, ~f=path => "." ++ path);
    let rec diet0 = (js: Js.t('a), path) =>
      switch (type_(js)) {
      | Object =>
        let dict: Js.Dict.t(Js.t('a)) = Reason.Obj.magic(js);
        let newDict = Js.Dict.empty();
        KanaeArray.iteri(
          Js.Dict.keys(dict),
          ~f=(~i as _, ~elt as key) => {
            let path = path ++ "." ++ key;
            let value = Js.Dict.unsafeGet(dict, key);
            if (KanaeList.contains(ignore, ~f=target => target == path)) {
              Js.Dict.set(newDict, key, value);
            } else if (! isZero(value)) {
              Js.Dict.set(newDict, key, diet0(Reason.Obj.magic(value), path));
            };
          }
        );
        Reason.Obj.magic(newDict);
      | _ => js
      };
    diet0(js, "");
  };
};

module Iterator = {
  type t('value);
  type elt('value);
  module Basic = {
    [@bs.send] external next : t('value) => elt('value) = "next";
    [@bs.get] external isDone : elt('value) => Js.boolean = "done";
    [@bs.get] external value : elt('value) => 'value = "value";
  };
  let next = iter : option('value) => {
    let elt = Basic.next(iter);
    Basic.isDone(elt) |> Js.to_bool ? None : Some(Basic.value(elt));
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

let fromBool = Boolean.to_js_boolean;

let fromList = KanaeList.toArray;

let fromOpt = Null.from_opt;

let fromOptMap = (opt, ~f) => KanaeOption.map(opt, ~f) |> Null.from_opt;