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
    std::array< char, w + 2 > buffer;
    auto greedyExponent = requiresTwoDigitExponent( real );
    const auto length = w + 2;
    const auto decimalDigits = 6 - greedyExponent;
    int consumedCharacters = snprintf( &buffer[0], length + 1, "%*.*E",
                                       length, decimalDigits, real );
    if ( consumedCharacters < 0 ){
      throw std::exception();
    }
    auto mantissaIt = buffer.begin() + greedyExponent;
    auto bufferEnd = mantissaIt + length - greedyExponent;
    auto sign = bufferEnd - 3;
    auto mantissaEnd = sign - 1;
    auto exponentIt = bufferEnd - 1 - greedyExponent;
    while( mantissaIt != mantissaEnd ){ *it++ = *mantissaIt++; }
    *it++ = *sign;
    while( exponentIt != bufferEnd ){ *it++ = *exponentIt++; }
  }
}
