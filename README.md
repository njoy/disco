Disco
==========
Disco is a header-only library to parse fixed-width text, providing constructs
which map one-to-one to Fortran format statements.

Minimal Example
-----------------

```c++
#include <assert.h>
#include <string>
#include "disco.hpp"

using namespace disco;

int main(){
  std::string source = "        1.0       1000 Hello\n";
  auto it = source.begin();
  auto end = source.end();
  
  double myDouble;
  int myInt;
  std::string myString;
  
  /* Equivalent Fortran Format: (E11.4, I11, 1X, A5 ) */
  using myFormat = Format< Exponential<11,4>, 
                           Integer<11>, 
                           ColumnPosition<1>, 
                           Character<5> >;
                           
  myFormat::read( it, end, myDouble, myInt, myString );
  
  assert( myDouble == 1.0 );
  assert( myInt == 1000 );
  assert( myString == "Hello" )l

}
```
