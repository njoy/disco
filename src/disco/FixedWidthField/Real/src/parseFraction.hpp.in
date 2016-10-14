template< typename Iterator >
static uint64_t
parseFraction( Iterator& it, uint16_t& position, bool& success ){
  uint64_t fraction = 0;
  success = ( *it == '.' );
  if ( success ){ 
    while ( position < Real::endPosition ) {
      ++position; ++it;
      if ( not isdigit( *it ) ) { break; }
      fraction = 10 * fraction + (*it - 48);
    }
  } 
  return fraction;
}
