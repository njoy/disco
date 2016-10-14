namespace disco {

template< uint16_t w, uint16_t m >
struct Integer : public FixedWidthField< w >{
  
  using FixedWidthField_ = FixedWidthField< w >;

  template< bool trust >
  using TrustTag = typename FixedWidthField_:: template TrustTag< trust >;
  
  struct Signed{};
  struct Unsigned{};

  struct WithPadding{};
  struct WithoutPadding{};

  using ZeroPaddingPolicy =
    std::conditional_t< m == std::numeric_limits<uint16_t>::max(),
                        WithoutPadding, WithPadding >;
  
  /* methods */
#include "disco/FixedWidthField/Integer/src/read.hpp"

  template< typename Iterator >
  static void write( Iterator& it ){
    ColumnPosition< w >::write( it );
  }
  
  template< typename Representation, typename Iterator >
  static void
  write( Representation integer, Iterator& it ){
    write( integer, it, ZeroPaddingPolicy() );
  }
  
#include "disco/FixedWidthField/Integer/src/write.hpp"

  /* helpers */

#include "disco/FixedWidthField/Integer/src/parseInteger.hpp"
  
};

}
