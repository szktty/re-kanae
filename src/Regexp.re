module Match = {
  module Basic = {
    type t = array(string);
    [@bs.get] external index : t => int = "index";
    [@bs.get] external input : t => string = "input";
  };
  type t = Basic.t;
  let index = Basic.index;
  let input = Basic.input;
  let last = t => t[0];
  let get = (t, ~i) => t[i + 1];
};

module Basic = {
  type t;
  type result = Js.Null.t(Match.Basic.t);
  [@bs.new] external create : (string, string) => t = "RegExp";
  [@bs.get] external global : t => Js.Boolean.t = "global";
  [@bs.get] external ignoreCase : t => Js.Boolean.t = "ignoreCase";
  [@bs.get] external lastIndex : t => Js.Boolean.t = "lastIndex";
  [@bs.get] external multiline : t => Js.Boolean.t = "multiline";
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
    List.map(flags, ~f=flag =>
      switch flag {
      | G => "g"
      | I => "i"
      | M => "m"
      | U => "u"
      | Y => "y"
      }
    )
    |> String.join;
  {t: Basic.create(pattern, flagsStr), pattern, flags};
};

let source = re => re.pattern;

let flags = re => re.flags;

let global = re => Basic.global(re) |> Js.toBool;

let ignoreCase = re => Basic.ignoreCase(re) |> Js.toBool;

let lastIndex = re => Basic.lastIndex(re) |> Js.toBool;

let multiline = re => Basic.multiline(re) |> Js.toBool;

let exec = (re, ~s) : option(Match.t) => Basic.exec(re, s) |> Js.Null.toOption;