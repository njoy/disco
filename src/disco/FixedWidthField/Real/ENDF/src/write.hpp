template< typename Representation, typename Iterator >
static void
write( Representation real, Iterator& it ){
  auto isInfinite = []( Representation real ){
    return std::abs( real ) ==
    std::numeric_limits<Representation>::infinity();
  };
  if ( isInfinite( real ) ){
    writeInfinity( it, ( real < 0 ), InfinityPrintingPolicy() );
  } else if ( isInvalid( real ) ){
    writeInvalid( it );
  } else {

    // Minimal exponent size is 2 (one sign and one digit)
    constexpr int MIN_EXPWIDTH = 2;
    // Minimal exponent for which we can use notation
    constexpr int MIN_EXPONENT = -2;

    // Decompose real
    double significand{ real };
    int exponent{ 0 };
    int expWidth{ MIN_EXPWIDTH };
    if( real != 0.0 ){
      exponent = std::floor( std::log10( std::abs( real ) ) );
      if( 0 < exponent ){
        significand /= std::pow( 10.0, exponent );
        expWidth += std::floor( std::log10( std::abs( exponent ) ) );
      } else if( 0 > exponent ){
        significand *= std::pow( 10.0, -exponent );
        expWidth += std::floor( std::log10( std::abs( exponent ) ) );
      }
    }

    unsigned int width = w - expWidth;
    unsigned int precision = width - 3;
    bool fixed = false;

    if( ( MIN_EXPONENT < exponent ) and ( exponent < ( w - 1 ) ) ){
      double max = std::pow( 10.0, expWidth );
      double remainder = std::abs( significand ) * std::pow( 10.0, precision );
      remainder -= std::floor( remainder );
      remainder *= max;

      if( ( 0.5 <= remainder ) and ( 0.5 <= ( max - remainder ) ) ){
         fixed = true;
         precision += expWidth;
         width += expWidth;
        
         if( exponent > static_cast< int >( precision ) ){
           precision = 0;
         } else if( 0 < exponent ) {
           precision -= exponent;
         }

      }
    }

    std::ostringstream buffer;
    buffer << std::setw(width) << std::fixed << std::showpoint
           << std::right << std::setprecision( precision );
    if( fixed ){
      if( 0 == precision ){
        buffer << static_cast< int >( real );
      }
      else {
        buffer << real;
      }
    }
    else {
      buffer << significand << std::showpos << exponent;
    }

    for( auto b : buffer.str() ){
      *it++ = b;
    }
  }
}
