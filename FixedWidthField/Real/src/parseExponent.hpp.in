template< typename Iterator >
static int64_t
parseExponent( Iterator& it, uint16_t& position ){
  int16_t sign = 1;
  
  auto boundCheck = []( auto p ){
    if ( p == Real::endPosition ){
      throw std::runtime_error ("illegal exponent format");
    }
  };

  boundCheck( position );
  const auto first = toupper(*it);
  switch( first ) {
  case 'E':
  case 'D':
    ++position; ++it;
    if ( *it == '+' ) {
      boundCheck( position );
      ++position; ++it;
    } else if ( *it == '-' ) {
      boundCheck( position );
      ++position; ++it;
      sign = -1;
    } else if ( not isdigit(*it) ) {
      throw std::runtime_error
        ("illegal character encountered while parsing real number");
    }
    break;
  case '+':
    ++position; ++it;
    break;
  case '-':
    ++position; ++it;
    sign = -1;
    break;
  default:
    throw std::runtime_error
      ("illegal character encountered while parsing real number");
  }
  uint64_t exponent = 0;

  if ( not isdigit( *it ) ){
    throw std::runtime_error
      ("illegal character encountered while parsing real number");
  }
  do {
    exponent = 10 * exponent + ( *it - 48 );
    if ( position == Real::endPosition ){ break; }
    ++position; ++it;
  } while ( isdigit( *it ) );

  return sign * exponent;
}
