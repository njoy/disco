struct ENDF : public Real< 11 > {

  static constexpr int w = 11;
  using Real_t = Real< w >;

  // below this value, you loose precision if fixed notation is used:
  static constexpr double minFixed = 0.1;
  // above this value, you loose precision if fixed notation is used
  static constexpr double maxFixed = 1e+10;
  // roundoff
  static constexpr double roundoff = 0.5;
  // minimal exponent width (sign, one digit)
  static constexpr int minExpWidth = 2;
  // characters excluded for fixed notation precision (optional sign,
  // first digit, decimal point)
  static constexpr int excluded = 3;

  using InfinityPrintingPolicy = Real::Full;

#include "disco/FixedWidthField/Real/ENDF/src/write.hpp"
#include "disco/FixedWidthField/Real/Scientific/src/writeInfinity.hpp"

};
