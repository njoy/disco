template< typename Iterator >
static uint16_t
skipPad( Iterator& it ){
  uint16_t position = 0;
  while( FixedWidthField::isSpace( *it ) ){
    ++it;
    if ( ++position == w ){ break; }
  }
  return position;
}