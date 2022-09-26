template< typename Iterator >
static uint64_t
parseFraction( Iterator& it, uint16_t& position, bool& success ) {

  uint64_t fraction = 0;
  success = false;
  if ( *it == '.' ) {

    const auto initialPosition = ++position;
    ++it;
    while ( position < width  ) {

      if ( not isdigit( *it ) ) { break; }
      //TODO: overflow check
      fraction = 10 * fraction + ( *it - 48 );
      ++position; ++it;
    }
    success = initialPosition != position;
  }
  return fraction;
}
