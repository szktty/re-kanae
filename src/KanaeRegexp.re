module Match = {
  module Basic = {
    type t = array(string);
    [@bs.get] external index : t => int = "index";
    [@bs.get] external input : t => string = "input";
  };
  type t = Basic.t;
  let index = Basic.index;
  let input = Basic.input;
  let last = t => KanaeArray.get(t, 0);
  let get = (t, ~i) => KanaeArray.get(t, i + 1);
};

module Basic = {
  type t;
  type result = Js.null(Match.Basic.t);
  [@bs.new] external create : (string, string) => t = "RegExp";
  [@bs.get] external global : t => Js.boolean = "global";
  [@bs.get] external ignoreCase : t => Js.boolean = "ignoreCase";
  [@bs.get] external lastIndex : t => Js.boolean = "lastIndex";
  [@bs.get] external multiline : t => Js.boolean = "multiline";
  [@bs.send] external exec : (t, string) => result = "exec";
};

type flag =
  | G
  | I
  | M
  | U
  | Y;

type t = {
  t: Basic.t,
  pattern: string,
  flags: list(flag)
};

let create = (~flags: list(flag)=[], pattern: string) => {
  let flagsStr =
    KanaeList.map(flags, ~f=flag =>
      switch flag {
      | G => "g"
      | I => "i"
      | M => "m"
      | U => "u"
      | Y => "y"
      }
    )
    |> KanaeString.join;
  {t: Basic.create(pattern, flagsStr), pattern, flags};
};

let source = re => re.pattern;

let flags = re => re.flags;

let global = re => Basic.global(re) |> Js.to_bool;

let ignoreCase = re => Basic.ignoreCase(re) |> Js.to_bool;

let lastIndex = re => Basic.lastIndex(re) |> Js.to_bool;

let multiline = re => Basic.multiline(re) |> Js.to_bool;

let exec = (re, ~s) : option(Match.t) => Basic.exec(re, s) |> Js.Null.to_opt;