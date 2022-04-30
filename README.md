# chemparse: A chemical formula parsing library in C++
chemparse is a library to parse chemical formula strings into compounds and elements.

# About
Makes doing my chem homework easier.

# Building
This library is distributed as both a static and dynamic/shared library. It also has a simple looped CLI where formulas can be inputted and data regarding them can be printed. Since it can be compiled with CMake, the only commands that need to be run are:
```sh
cmake -B build
cmake --build build
```
Once that's done, the binary can be found in `build/bin` and the libraries can be found in `build/lib`.

## Credits
JSON Data: https://github.com/Bowserinator/Periodic-Table-JSON  
JSON Parser: https://github.com/nlohmann/json
