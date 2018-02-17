module Basic = {
  type t;
  [@bs.module] external shajs : string => t = "shajs";
  [@bs.send] external update : (t, string) => unit = "update";
  [@bs.send] external digest0 : t => string = "digest";
  [@bs.send] external digest : (t, string) => string = "digest";
};

type t;

type algorithm =
  | SHA_256
  | SHA_384
  | SHA_512;

let create = alg => {
  let name =
    switch alg {
    | SHA_256 => "sha256"
    | SHA_384 => "sha384"
    | SHA_512 => "sha512"
    };
  Basic.shajs(name);
};

let update = (hash, ~data) => Basic.update(hash, data);

let digest = Basic.digest0;

let hexDigest = hash => Basic.digest(hash, "hex");