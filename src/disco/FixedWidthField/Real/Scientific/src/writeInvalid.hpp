template< typename Iterator >
static void
writeInvalid( Iterator& it ){
  auto remainingPositions = w;
  while ( remainingPositions-- ){
    *it++ = '*';
  }
}
