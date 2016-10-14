template< typename Iterator >
static void
writeZero( Iterator& it ){
  auto remainingBlanks = w - d - 2 - exponentDigits - 2;
  while ( remainingBlanks-- > 0 ){ *it++ = ' '; }
  *it++ = '0';
  *it++ = '.';
  auto remainingFractionDigits = d;
  while ( remainingFractionDigits-- ){
    *it++ = '0';
  }
  *it++ = 'E';
  *it++ = '+';
  auto remainingExponentDigits = exponentDigits;
  while ( remainingExponentDigits-- ){
    *it++ = '0';
  }
}
