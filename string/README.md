This project was created to explore C++ libraries.

### String

*Extending dynamic string class, simplified version of C++ standart library `std::string` class.[additional info](https://en.cppreference.com/w/cpp/string/basic_string).*

##### Details

String class has effective expanding strategy - multiplicative scheme.

`String` interface includes:
* Implicit constructor creating empty string;
* Constructor from `size` and `symbol`;.
* Constructor from C-style string, `const char *`;
* Constructor from array `const char*` and the number of first elements which would be copied;
* destructor
* copy constructor
* copy assignment operator
* access to the element by `[]`;
* access to the element using `At` method, including exception `StringOutOfRange`;
* `Front()` and `Back()` methods;
* `CStr()` and `Data()` methods, returning a pointer to the beginning of the string;
* `Empty()` (boolean) and `Clear()` (size value to 0) method;
* `Size()`, `Capacity()` and `Length()` methods;
* `Swap(other)` method;
* `PopBack()` method, deleting the last symbol;
* `PushBack(symbol)` method, adding `symbol` to the end of the string;
* `+=` operation, adding another string to the current;
* `Resize(new_size, symbol)` method, changes the `size` to the `new_size`. If `new_size > size`, filling the space with `symbol`;
* `Reserve(new_capacity)` method - changing the capacity to `max(new_capacity, текущая вместимость)`;
* `ShrinkToFit()` method, decreasing capacity to size;
* Concatenation using operation `+`;
* Comparisons (`<`, `>`, `<=`, `>=`, `==`, `!=`), based on the  lexicographic order;
* Stream output.


# This project was created by Ksenija Okuneva 
# December 2022
