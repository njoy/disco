namespace disco {

template< uint16_t w, uint16_t d >
struct FixedPoint : public Real< w > {

  using Real_t = Real< w >;

  static constexpr int64_t maxPositiveValue =
    integerExponentiation< int64_t >::cache( int(w) - d - 1 );

  static constexpr int64_t maxNegativeValue =
    -1 * integerExponentiation< int64_t >::cache( int(w) - d - 2 );
  
  using InfinityPrintingPolicy =
    std::conditional_t
    < ( w > 8 ),
      typename Real_t::Full,
      std::conditional_t< ( w < 8 ),
                          typename Real_t::Partial,
                          typename Real_t::PartialNegative > >;
                 
  template< typename Representation >
  static bool
  isInvalid( Representation real ){
    return ( ( ( int(w) - d - 1 - ( real < 0 ) ) < 0 )
             || ( real <= maxNegativeValue )
             || ( real >= maxPositiveValue ) );
  }
  
#include "disco/FixedWidthField/Real/FixedPoint/src/write.hpp" 
#include "disco/FixedWidthField/Real/Scientific/src/writeInvalid.hpp"
#include "disco/FixedWidthField/Real/Scientific/src/writeInfinity.hpp"
 
};

}
