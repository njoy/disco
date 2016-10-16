template< typename Representation, typename Iterator >
static void
write( Representation real, Iterator& it ){
  auto isInfinite = []( Representation real ){
    return std::abs( real ) ==
    std::numeric_limits<Representation>::infinity();
  };
  if ( isInfinite( real ) ){
    writeInfinity( it, ( real < 0 ), InfinityPrintingPolicy() );
  } else if ( isInvalid( real, ExponentPolicy() ) ){
    writeInvalid( it );
  } else if ( real == 0.0 ){
    writeZero( it );
  } else {    
    write( real, it, ExponentPolicy() );
  }
}

template< typename Representation, typename Iterator >
static void
write( Representation real, Iterator& it, MayNotConsumeExponent ){
#ifdef __MINGW32__
   const int requiredDigits =
    Real_t::noDigits( std::ceil( std::abs( std::log10( std::abs( real ) ) ) ) ) - 1;
#else
   const int requiredDigits =
    Real_t::noDigits( std::ceil( std::abs( std::log10( std::abs( real ) ) ) ) );
#endif
  ( requiredDigits <= exponentDigits ) ? 
    writeWithoutConsumption( real, it, requiredDigits ) :
    writeInvalid( it );
}

template< typename Representation, typename Iterator >
static void
write( Representation real, Iterator& it, MayConsumeExponent ){
  const int requiredDigits =
    Real_t::noDigits( std::ceil( std::abs( std::log10( std::abs( real ) ) ) ) );
  ( requiredDigits <= exponentDigits ) ? 
    writeWithoutConsumption( real, it, requiredDigits ) :
    ( requiredDigits <= ( exponentDigits + 1 ) ) ?
    writeWithConsumption( real, it ) :
    writeInvalid( it );
}
