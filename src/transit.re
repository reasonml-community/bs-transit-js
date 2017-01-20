type reader;

type format =
  | Json
  | JsonVerbose;

let string_of_format t =>
  switch t {
  | Json => "json"
  | JsonVerbose => "json-verbose"
  };

external raw_reader : string => 'options => reader =
  "reader" [@@bs.val] [@@bs.module "transit-js"];

let reader ::format=Json options => {
  let readerType = string_of_format format;
  raw_reader readerType options
};

external read : reader => 'a => 'b = "read" [@@bs.send];

type writehandler;

external makeWriteHandler : 'a => writehandler =
  "makeWriteHandler" [@@bs.val] [@@bs.module "transit-js"];

type writer;

type transitMap;

external map : 'handlers => transitMap = "map" [@@bs.val] [@@bs.module "transit-js"];

external raw_writer : string => 'handler => writer =
  "writer" [@@bs.val] [@@bs.module "transit-js"];

let writer ::format=Json options => {
  let writerType = string_of_format format;
  raw_writer writerType {"handlers": options}
};

external write : writer => 'a => 'b = "write" [@@bs.send];
