template< typename Iterator >
static uint64_t
parseBase( Iterator& it, uint16_t& position, bool& success ){
  uint64_t base = ( success = isdigit( *it ) ) ? (*it - 48) : 0;
  if ( success ){
    ++position; ++it;
    while ( position < width ) {
      if ( not isdigit( *it ) ) { break; }
      // TODO: overflow check
      base = ( 10 * base ) + (*it - 48);
      ++position; ++it;
    }
  }
  return base;
}
