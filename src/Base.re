let log = Js.log;






let absEqual = (==);

let (==) = (_: [ | `Use_absEqual], _: [ | `Use_absEqual]) : [ | `Use_absEqual] => `Use_absEqual;

let (!=) = (_: [ | `Use_absEqual], _: [ | `Use_absEqual]) : [ | `Use_absEqual] => `Use_absEqual;