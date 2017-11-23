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
  const int requiredDigits =
    noDigits( std::ceil( std::abs( std::log10( std::abs( real ) ) ) ) );
  if ( requiredDigits <= exponentDigits ){
    writeWithoutConsumption( real, it, requiredDigits );
  } else {
    writeInvalid( it );
  }
}

template< typename Representation, typename Iterator >
static void
write( Representation real, Iterator& it, MayConsumeExponent ){
  const int requiredDigits =
    noDigits( std::ceil( std::abs( std::log10( std::abs( real ) ) ) ) );
  if ( requiredDigits <= exponentDigits ){
    writeWithoutConsumption( real, it, requiredDigits );
  } else if ( requiredDigits <= ( exponentDigits + 1 ) ){
    writeWithConsumption( real, it );
  } else {
    writeInvalid( it );
  }
}
