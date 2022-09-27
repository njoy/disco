template< typename Iterator >
static uint16_t
whiteSpace( Iterator& it ) {

  uint16_t position = 0;
  while( FixedWidthField::isSpace( *it ) and ++position != w ) {

    ++it;
  }
  return position;
}

template< typename Iterator >
static bool
whiteSpace( Iterator& it, uint16_t position ) {

  while( ++position <= w and FixedWidthField::isSpace( *it ) ) { ++it; }
  return position > w
         or FixedWidthField::isNewline( *it, it )
         or FixedWidthField::isEOF( *it );
}
