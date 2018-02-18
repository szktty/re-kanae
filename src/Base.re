module Array = Array;

module Binary = Binary;

module Bool = Bool;

module Char = Char;

module Comparable = Comparable;

module Collection = Collection;

module Date = Date;

module Digest = Digest;

module Error = Error;

module Float = Float;

module Int = Int;

module Js = Js;

module JSON = JSON;

module JSONable = JSONable;

module List = List;

module Map = Map;

module Option = Option;

module OrError = OrError;

module Path = Path;

module Promise = Promise;

module Random = Random;

module Reader = Reader;

module Reason = Builtin.Reason;

module Regexp = Regexp;

module Result = Result;

module String = String;

module Time = Time;

module WithReturn = WithReturn;

module Writer = Writer;

let show = Js.log;

let abstEqual = (==);

let (==) =
    (_: [ | `Use_abstEqual], _: [ | `Use_abstEqual])
    : [ | `Use_abstEqual] => `Use_abstEqual;

let (!=) =
    (_: [ | `Use_abstEqual], _: [ | `Use_abstEqual])
    : [ | `Use_abstEqual] => `Use_abstEqual;

let withReturn = WithReturn.withReturn;