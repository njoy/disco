template< typename Representation, typename Iterator >
static void
writeWithoutConsumption
( Representation real, Iterator& it, int usedExponentDigits ){
  std::array< char, w+1  > buffer;
  int consumedCharacters = snprintf( &buffer[0], w+1, "%*.*E", w, d, real);
  const auto bufferExponentPositions = std::max( usedExponentDigits, 2 );
    
  auto mantissaIt = buffer.begin();
  const auto exponentEnd = mantissaIt + consumedCharacters;
  auto exponentIt = exponentEnd - bufferExponentPositions - 2;
  const auto mantissaEnd = exponentIt;
  #ifdef __MINGW32__
  exponentDigitDifference -= 1;
  #endif
  int exponentDigitDifference = int( exponentDigits ) - bufferExponentPositions;
  while ( exponentDigitDifference++ < 0 ){ *it++ = ' '; }
  while ( exponentDigitDifference-- > 1 ){ ++mantissaIt; }
  while ( mantissaIt != mantissaEnd ){ *it++ = *mantissaIt++; }
  *it++ = *exponentIt++; // exponent symbol
  *it++ = *exponentIt++; // exponent sign
  exponentDigitDifference--;
  exponentDigitDifference = int( exponentDigits ) - bufferExponentPositions;
  #ifdef __MINGW32__
  exponentDigitDifference -= 1;
  #endif
  while ( exponentDigitDifference++ < 0 ){ ++exponentIt; }
  while ( exponentDigitDifference-- > 1 ){ *it++ = '0'; }
  while ( exponentIt != exponentEnd ){ *it++ = *exponentIt++; }
}
