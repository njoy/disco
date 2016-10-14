template< typename Iterator >
static void
write( Iterator& it ){
  auto remainingCharacters = w;
  while ( remainingCharacters-- ){ *it++ = ' '; }
}
