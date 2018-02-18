type return('a) = {return: 'b .'a => 'b};

let withReturn: (return('a) => 'a) => 'a;