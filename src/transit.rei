type format;

type reader;

let reader: format::format? => 'options => reader;

type writer;

external read : reader => 'a => 'b = "read" [@@bs.send];

type writehandler;

external makeWriteHandler : 'a => writehandler =
  "makeWriteHandler" [@@bs.val] [@@bs.module "transit-js"];

type transitMap;

external map : 'handlers => transitMap = "map" [@@bs.val] [@@bs.module "transit-js"];

let writer: format::format? => transitMap => writer;

external write : writer => 'a => 'b = "write" [@@bs.send];
