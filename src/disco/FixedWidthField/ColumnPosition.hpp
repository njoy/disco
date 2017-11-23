template< uint16_t w = 1 >
struct ColumnPosition : public FixedWidthField< w >{
  
  using FixedWidthField_ = FixedWidthField< w >;

  /* methods */
#include "disco/FixedWidthField/ColumnPosition/src/read.hpp"
#include "disco/FixedWidthField/ColumnPosition/src/write.hpp"
  
};

