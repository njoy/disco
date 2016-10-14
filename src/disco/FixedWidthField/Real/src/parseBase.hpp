template< typename Iterator >
static uint64_t
parseBase( Iterator& it, uint16_t& position, bool& success ){
  uint64_t base = ( success = isdigit( *it ) ) ? (*it - 48) : 0 ;
  if ( success ){ 
    while ( position < Real::endPosition ) {
      ++position; ++it;
      if ( not isdigit( *it ) ) { break; }
      base = ( 10 * base ) + (*it - 48);
    }
  }
  return base;
}