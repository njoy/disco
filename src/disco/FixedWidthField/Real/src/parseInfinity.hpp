template< typename Iterator >
static bool
parseInfinity( Iterator& it, uint16_t& position ) {

  auto canProceed = [&it]() {

    return not ( FixedWidthField< w >::isEOF( *it )
		 or FixedWidthField< w >::isNewline( *it, it ) );
  };

  const auto remainingWidth = int( w ) - position;
  bool success = false;
  if ( remainingWidth >= 3 ) {

    position += 3;
    success =
      ( toupper( *it++ ) == 'I' )
      and ( canProceed() and toupper( *it++ ) == 'N' )
      and ( canProceed() and toupper( *it++ ) == 'F' );
    if ( success and remainingWidth >= 8 and toupper( *it ) == 'I' ) {

      position += 5;
      ++it;
      success =
        ( canProceed() and toupper( *it++ ) == 'N' )
      	and ( canProceed() and toupper( *it++ ) == 'I' )
      	and ( canProceed() and toupper( *it++ ) == 'T' )
      	and ( canProceed() and toupper( *it++ ) == 'Y' );
    }
  }
  return success;
}
