struct ENDF : public Real< 11 > {

  static constexpr int w = 11;
  using Real_t = Real< w >;

  // below this value, you loose precision if fixed notation is used:
  static constexpr double minFixed = 0.1;
  // above this value, you loose precision if fixed notation is used
  static constexpr double maxFixed = 1e+10;

  static constexpr double maxValue = 1E50;
  static constexpr double minValue = 1E-50;

  template< typename Representation >
  static constexpr bool
  requiresTwoDigitExponent( Representation real ){
    return ( ( real != 0 )
             && ( ( std::abs( real ) >= 1E10 )
                  || ( std::abs( real ) < 1E-9 ) ) );
  }

  using InfinityPrintingPolicy = Real::Full;

#include "disco/FixedWidthField/Real/ENDF/src/write.hpp"
#include "disco/FixedWidthField/Real/Scientific/src/writeInfinity.hpp"

};
