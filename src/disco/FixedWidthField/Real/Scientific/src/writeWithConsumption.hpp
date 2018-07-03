template< typename Representation, typename Iterator >
static void
writeWithConsumption( Representation real, Iterator& it ){
  static constexpr auto fieldRequirement = w + 2;
  static constexpr auto precisionRequirement = d + 8;
  static constexpr auto sufficient =
    fieldRequirement > precisionRequirement ?
    fieldRequirement : precisionRequirement;
  std::array< char, sufficient > buffer;
  const int consumedCharacters =
    sprintf( &buffer[0], "%*.*E", w+1, d, real);

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
