template< typename Representation, typename Iterator >
static void
writeWithConsumption( Representation real, Iterator& it ){
  std::array< char, w+2 > buffer;
  const int consumedCharacters = snprintf( &buffer[0], w+2, "%*.*E", w, d, real);
  
  auto mantissaIt = buffer.begin();
  const auto exponentEnd = mantissaIt + consumedCharacters;
  auto exponentIt = exponentEnd - 4;
  const auto mantissaEnd = exponentIt - 1;

  auto requiresLeadingBlanks = w + 1 - consumedCharacters;
  while (requiresLeadingBlanks--){
    *it++ = ' ';
  }
  while ( mantissaIt != mantissaEnd ){ *it++ = *mantissaIt++; }
  while ( exponentIt != exponentEnd ){ *it++ = *exponentIt++; }
}
