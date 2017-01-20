module Coordinate = {
  type t = {x: int, y: int};
  let make x y => {x, y};

  /**
   Transit read & write helpers
   */
  let writerSpec =
    Transit.makeWriteHandler ({pub tag () => "coord"; pub rep {x, y} () => (x, y)} [@bs]);
  let readerSpec (x, y) => {x, y};
};

module Size = {
  type t = {width: int, height: int};
  let make width height => {width, height};

  /**
   Transit read & write helpers
   */
  let writerSpec =
    Transit.makeWriteHandler ({pub tag () => "size"; pub rep v () => (v.width, v.height)} [@bs]);
  let readerSpec (width, height) => {width, height};
};

module Language = {
  type t =
    | Ocaml
    | Lisp
    | Other;

  /**
   Transit read & write helpers
   */
  let writerSpec = {
    pub tag () => "lang";
    pub rep v () =>
      switch v {
      | Ocaml => 0
      | Lisp => 1
      | Other => 3
      }
  };
  let readerSpec rep =>
    switch rep {
    | 0 => Ocaml
    | 1 => Lisp
    | _ => Other
    };
};

module Rectangle = {
  type t = {origin: Coordinate.t, size: Size.t};
  let make origin size => {origin, size};

  /**
   Transit read & write helpers
   */
  let writerSpec =
    Transit.makeWriteHandler (
      {pub tag () => "coord"; pub rep {origin, size} () => (origin, size)} [@bs]
    );
  let readerSpec (origin, size) => {origin, size};
};

let reader = Transit.reader {"handlers": {point: Coordinate.readerSpec, size: Size.writerSpec}};

let writer =
  Transit.writer @@
  /*
   In javascript this is a transit map from function constructors as keys to
   writehandlers as values. Function constructors as keys only
   matter if you have something like:
   var Point = function(x, y) { this.x = x; this.y = y; };
   (I think, need to investigate more)
    */
  Transit.map (
    "Coordinate",
    Coordinate.writerSpec,
    "Size",
    Size.writerSpec,
    "Language",
    Language.writerSpec,
    "Rectangle",
    Rectangle.writerSpec
  );

let encodedCoordinate = Transit.write writer (Coordinate.make 8 8);

let encodedSize = Transit.write writer (Size.make 5 5);

let encodedLanguage = Transit.write writer Language.Ocaml;

let encodedRectangle =
  Transit.write writer (Rectangle.make (Coordinate.make 0 0) (Size.make 10 10));

let coordinate: Coordinate.t = Transit.read reader encodedCoordinate;

let size: Size.t = Transit.read reader encodedSize;

let lang: Language.t = Transit.read reader encodedLanguage;

let rect: Rectangle.t = Transit.read reader encodedRectangle;

let () =
  Language.(
    switch lang {
    | Ocaml => print_endline "OCaml!!!"
    | Lisp => print_endline "The most intelligent way to misuse a computer"
    | _ => print_endline "other stuff"
    }
  );
