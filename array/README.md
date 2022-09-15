This project was created to explore C++ libraries.

#### Intro
 
Array.h is an analogy to `std::array<T, N>` from the C++11 standart library. This template is a coverage to the C-style array. It has the advantages of C-style arrays like:
 - fixed size
 - location at stack memory
All the functionality and effectivity also remains.
 
And has not many of the downsides:
 - not being eventually converted to pointers
 - have no problems passing as an argument to the function
 - works the assignment operation

[More information.](https://en.cppreference.com/w/cpp/container/array)

#### Details of the realization

`Array` is a simplified version of `std::array`. It has two parameters, the type of data in the array and the size of the array.
Aggregate initialization can be following:

```c++
int arr[4]{1, 2, 3};  // array {1, 2, 3, 0}
Array<int, 4> other_arr{1, 2, 3};  // same array
```
Realized methods:
* Access to an item by index;
* `At(size_t idx)` method (secured access by index, throws exception `ArrayOutOfRange`);
* `Front()` and `Back()` methods (access to the first and the last elements);
* `Data()` method (returns pointer to the array);
* `Size()` and `Empty()` methods;
* `Fill(const T& value)` method;
* `Swap(Array<T, N>& other)` method.

**Also there is a testing program.**

---

### In following updates: implemetation of array traits

What may be realized:

* `GetSize(array)`, returning the number of alements in the array, 0 if `array` is not a C-styled array;
* `GetRank(array)`, returning the number of coordinates of multiarray `array`;
* `GetNumElements(array)`, returning the total number of elements in the multiarray `array`.

```c++
#define ARRAY_TRAITS_IMPLEMENTED
```
# This project was created by Ksenija Okuneva 
# December 2022
