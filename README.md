LLVM based parser in C++ for simpler BASIC.

**Course**: [Compilers], Monsoon 2019<br>
**Taught by**: Prof. Suresh Purini
<br>
<br>

[Compilers]: https://github.com/iiithf/compilers

`e**.bas` are example input programs to scanner.
use `./scanner <input file>` to run scanner.


## notes

`26.10.2019`
- added several inbuilt qb-functions
- could not depointer `string` in `Value`
- (this is not allowed in c++ wo copy con.)
- parser does not allow `x` to be both `Id`/ `Fn`
- there can be unstructured goto anywhere
- using string stream makes `s()` convenient
- virtual function called `ins` for insertion
- operator overloading with `ostream`.
- `friend` function used as multiple includes
- was reusing `x` in parser which caused problems


`27.06.2019`
- ast needs transformation

`30.06.2019`
- how do you have line numbers or labels in lines
- how do you keep track of it
- close needs to validates es to ints and call1 close
