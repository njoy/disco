template< typename Representation, typename Iterator >
static void
writeWithoutConsumption
( Representation real, Iterator& it, int usedExponentDigits ){
  static constexpr auto fieldRequirement = w + 1;
  static constexpr auto precisionRequirement = d + 8;
  static constexpr auto sufficient =
    fieldRequirement > precisionRequirement ?
    fieldRequirement : precisionRequirement;
  std::array< char, sufficient  > buffer;
  int consumedCharacters = sprintf( &buffer[0], "%*.*E", w, d, real);

  const auto bufferExponentPositions = std::max( usedExponentDigits, 2 );

  auto mantissaIt = buffer.begin();
  const auto exponentEnd = mantissaIt + consumedCharacters;
  auto exponentIt = exponentEnd - bufferExponentPositions - 2;
  const auto mantissaEnd = exponentIt;

  int exponentDigitDifference = int( exponentDigits ) - bufferExponentPositions;
  while ( exponentDigitDifference++ < 0 ){ *it++ = ' '; }
  while ( exponentDigitDifference-- > 1 ){ ++mantissaIt; }
  while ( mantissaIt != mantissaEnd ){ *it++ = *mantissaIt++; }
  *it++ = *exponentIt++; // exponent symbol
  *it++ = *exponentIt++; // exponent sign
  exponentDigitDifference--;
  exponentDigitDifference = int( exponentDigits ) - bufferExponentPositions;

  while ( exponentDigitDifference++ < 0 ){ ++exponentIt; }
  while ( exponentDigitDifference-- > 1 ){ *it++ = '0'; }
  while ( exponentIt != exponentEnd ){ *it++ = *exponentIt++; }
}
