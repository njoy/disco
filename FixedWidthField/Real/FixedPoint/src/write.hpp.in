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
    std::array< char, w+1  > buffer;
    int consumedCharacters = snprintf( &buffer[0], w+1, "%#*.*F", w, d, real);
    if ( consumedCharacters < 0 ){
      throw std::exception();
    }
    auto bufferIt = buffer.begin();
    auto bufferEnd = buffer.end() - 1;
    while( bufferIt != bufferEnd ){ *it++ = *bufferIt++; }
  }
}
