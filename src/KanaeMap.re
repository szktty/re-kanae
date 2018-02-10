module type S = {
  type key;
  type t('value);
  let empty: unit => t('value);
  let isEmpty: t('value) => bool;
  let singleton: (key, 'value) => t('value);
  let length: t('value) => int;
  let get: (t('value), ~key: key) => option('value);
  let getExn: (t('value), ~key: key) => 'value;
  let set: (t('value), ~key: key, ~value: 'value) => unit;
  let remove: (t('value), ~key: key) => unit;
  let iter: (t('value), ~f: (~key: key, ~value: 'value) => unit) => unit;
  let map: (t('value1), ~f: 'value1 => 'value2) => t('value2);
  let reduce:
    (
      t('value),
      ~init: 'accu,
      ~f: (~init: 'accu, ~key: key, ~value: 'value) => 'accu
    ) =>
    'accu;
  let filter:
    (t('value), ~f: (~key: key, ~value: 'value) => bool) => t('value);
};

module Basic = {
  type t('key, 'value);
  [@bs.new] external create : unit => t('key, 'value) = "Map";
  [@bs.get] external size : t('key, 'value) => int = "size";
  [@bs.send]
  external get : (t('key, 'value), 'key) => Js.nullable('value) = "get";
  [@bs.send] external set : (t('key, 'value), 'key, 'value) => unit = "set";
  [@bs.send] external delete : (t('key, 'value), 'key) => unit = "delete";
  [@bs.send]
  external entries : t('key, 'value) => KanaeJs.Iterator.t(array('elt)) =
    "entries";
};

module Make = (Key: KanaeComparable.S) : (S with type key := Key.t) => {
  type key = Key.t;
  type t('value) = Basic.t(key, 'value);
  let length = m => Basic.size(m);
  let empty = () => Basic.create();
  let isEmpty = m => length(m) == 0;
  let singleton = (k, v) => {
    let m = Basic.create();
    Basic.set(m, k, v);
    m;
  };
  let get = (m, ~key) => Js.toOption(Basic.get(m, key));
  let getExn = (m, ~key) => KanaeOption.valueExn(get(m, key));
  let set = (m, ~key, ~value) => Basic.set(m, key, value);
  let remove = (m, ~key) => Basic.delete(m, key);
  let iter = (m: t('value), ~f: (~key: key, ~value: 'value) => unit) =>
    KanaeJs.Iterator.iter(Basic.entries(m), ~f=(elt: array('pair)) =>
      f(~key=Obj.magic(elt[0]), ~value=Obj.magic(elt[1]))
    );
  let map = (m, ~f) => {
    let m1 = empty();
    iter(m, ~f=(~key, ~value) => set(m1, ~key, ~value=f(value)));
    m1;
  };
  let reduce = (m, ~init, ~f) => {
    let accu = ref(init);
    iter(m, ~f=(~key, ~value) => accu := f(~init=accu^, ~key, ~value));
    accu^;
  };
  let filter = (m, ~f) => {
    let m1 = empty();
    iter(m, ~f=(~key, ~value) =>
      if (f(~key, ~value)) {
        set(m1, ~key, ~value);
      }
    );
    m1;
  };
};

/* test */
let value = ();