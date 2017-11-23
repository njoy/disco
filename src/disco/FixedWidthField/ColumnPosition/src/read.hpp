template< typename Iterator >
static void
read( Iterator& it, const Iterator& ){
  auto remainingCharacters = w;
  while( remainingCharacters--
	 and not ( FixedWidthField_::isNewline( *it, it )
		   or FixedWidthField_::isEOF( *it ) ) ){ ++it; }
}
