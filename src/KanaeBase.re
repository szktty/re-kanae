let log = Js.log;

let physEqual = (===);

let (===) =
    (_: [ | `Use_physEqual], _: [ | `Use_physEqual])
    : [ | `Use_physEqual] => `Use_physEqual;

let (!==) =
    (_: [ | `Use_physEqual], _: [ | `Use_physEqual])
    : [ | `Use_physEqual] => `Use_physEqual;

include Js.Promise;