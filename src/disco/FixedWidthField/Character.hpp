template< uint16_t w = 1 >
struct Character : public FixedWidthField< w >{

  using FixedWidthField_ = FixedWidthField< w >;

  /* methods */
  #include "disco/FixedWidthField/Character/src/read.hpp"
  #include "disco/FixedWidthField/Character/src/write.hpp"

  template< typename Iterator >
  static void write( Iterator& it ){
    ColumnPosition< w >::write( it );
  }
};
