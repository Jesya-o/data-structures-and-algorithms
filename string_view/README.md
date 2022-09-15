This project was created to explore C++ libraries.

### String_view

*String_view is an simplified analogy to the `std::string_view` C++17.*

It is a class based on C-style strings. However, string_view has following advantages:
* getting the size O(1);
* built_in comparisons;
* secured data access.

Interface includes:
* `Front()`, `Back()`, `Size()`, `Length()`, `Empty()`, `Data()`, `Swap(String&)`; 
* `At`, including exception `StringViewOutOfRange`;
* `Substr(size_t pos, size_t count = -1)` - substring with beginning at `pos` and length `min(count, Size() - pos)`, including exception `StringViewOutOfRange`;
* `RemoveSuffix(size_t suffix_size)`, moving end on `suffix_size`;
* `RemovePrefix(size_t prefix_size)`, moving beginning on `prefix_size`;
* `[]` operation;
* Implicit constructor (`nullptr`);
* Constructor from `const char *`;
* Constructor from `const char *` and `size_t`;
* `begin()`, `cbegin()`, `rbegin()`, `crbegin()`, `end()`, `cend()`, `rend()`, `crend()`, `begin()`, `end()`, `rbegin()`, `rend()`;

### This project was created by Ksenija Okuneva 
### December 2022
