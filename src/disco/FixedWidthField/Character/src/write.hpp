template< typename Iterator >
static void
write( const std::string& characterString, Iterator& it ){
  auto stringIt = characterString.begin();
  int difference = w - int(characterString.size());
  auto stringEnd = characterString.end() + ( difference < 0 ) * difference;
  while ( difference-- > 0 ){ *it++ = ' '; }
  while ( stringIt != stringEnd ){ *it++ = *stringIt++; }
}
