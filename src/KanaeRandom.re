module Basic = {
  type t;
  [@bs.module "mersenne"] [@bs.new]
  external create : unit => t = "MersenneTwister19937";
  [@bs.send] external seed : (t, int) => unit = "init_genrand";
  [@bs.send] external int32 : t => int = "genrand_int32";
  [@bs.send] external real1 : t => float = "genrand_real1";
  [@bs.send] external real2 : t => float = "genrand_real2";
  [@bs.send] external real3 : t => float = "genrand_real3";
};

let create = Basic.create;

let seed = (gen, ~n: int) => Basic.seed(gen, n);

let int32 = (gen, ~bound: int) => Basic.int32(gen) mod bound;

let float = Basic.real2;

let bool = gen => float(gen) < 0.5;