# Kanae

ReasonML base library.

## Usage

Write this line at the top of source files.

```
open Kanae;
```

## API

This library shadows the standard library modules. Use prefix ``Reason.`` to access the modules (e.g., ``Reason.List``).

- Array
- Bool: Boolean operations
- Char
- Comparable: Functor which makes a module has comparable data and comparison functions
- Error
- Float
- Int
- Js: ``Js`` module extension
- JSON
- JSONable: Functor which makes a module has JSON conversion functions
- List
- Map: Map data structure which uses the JavaScript feature
- Option: Optional value operations
- OrError: Shorthand for ``Result('a, Error.t)``
- Path: File path operations
- Promise
- Regexp: Regular expression which uses the JavaScript feature
- Result: Represents a result value or error
- String
