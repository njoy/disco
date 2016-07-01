template< typename Iterator, bool trust = true >
static void
read( Iterator& it, const Iterator& end ){
  FixedWidthField_::verifyWidth_( it, end, TrustTag< trust >() );
  auto remainingCharacters = w;
  while( remainingCharacters--
         and not ( FixedWidthField_::isNewline( *it )
                   or FixedWidthField_::isEOF( *it ) ) ){ ++it; }
}
