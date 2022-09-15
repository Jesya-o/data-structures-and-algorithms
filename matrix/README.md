### MatrixArray

This class helps working with matrixes of fixed size which cannot be changed after the compilation.
It gives the following advantages:
 - effectiveness due to the possibility to use nondynamic arrays;
 - precaution of wrong operations with matrixes (multiplication errors, invertation errors).

#### Realized methods, functions and operations

* `RowsNumber()` and `ColumnsNumber()`;
* `()` operation, access to the element and changing possibility;
* `At` method, access to the element, throws the exception `MatrixOutOfRange` in case of going out of the matrix's range;
* `GetTransposed(matrix)` function, returns transposed matrix;
* Addition, difference operations and assignments with restrictions;
* Multiplication and deletion on the number operations and assignments;
* Comparison operations for the matrixes of same size;
* Stream input and output. 


# This project was created by Ksenija Okuneva 
# December 2022
