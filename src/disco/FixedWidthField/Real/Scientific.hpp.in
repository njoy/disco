namespace disco {

template< uint16_t w, uint16_t d, uint16_t e >
struct Scientific : public Real< w > {

  using Real_t = Real< w >;
  using MayConsumeExponent = typename Real_t::MayConsumeExponent;
  using MayNotConsumeExponent = typename Real_t::MayNotConsumeExponent;

  using InfinityPrintingPolicy =
    std::conditional_t
    < (w > 8 ),
      typename Real_t::Full,
      std::conditional_t
      < ( w < 8 ),
        typename Real_t::Partial,
        typename Real_t::PartialNegative > >;
  
  using ExponentPolicy =
    std::conditional_t< e == std::numeric_limits< uint16_t >::max(),
                        MayConsumeExponent, MayNotConsumeExponent >;

  static constexpr int exponentDigits =
    ( e == std::numeric_limits< uint16_t >::max() ) ? 2 : e;

  template< typename Representation >
  static bool
  isInvalid( Representation real, MayConsumeExponent ){
    return ( int(w) - d - exponentDigits - 3 - ( real < 0 ) ) < 0;
  }

  template< typename Representation >
  static bool
  isInvalid( Representation real, MayNotConsumeExponent ){
    return ( int(w) - d - exponentDigits - 4 - ( real < 0 ) ) < 0;
  }

  using Real_t::write;
  
#include "disco/FixedWidthField/Real/Scientific/src/write.hpp" 
#include "disco/FixedWidthField/Real/Scientific/src/writeWithoutConsumption.hpp" 
#include "disco/FixedWidthField/Real/Scientific/src/writeWithConsumption.hpp" 
#include "disco/FixedWidthField/Real/Scientific/src/writeInvalid.hpp"
#include "disco/FixedWidthField/Real/Scientific/src/writeZero.hpp"
#include "disco/FixedWidthField/Real/Scientific/src/writeInfinity.hpp"
  
};

}
