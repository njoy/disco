template< typename Iterator >
static int64_t
parseExponent( Iterator& it, uint16_t& position ){
  int16_t sign = 1;
  
  auto boundCheck = []( auto p ){
    if ( unlikely( p == Real::endPosition ) ){
      throw std::runtime_error ("illegal exponent format");
    }
  };
 
  const auto first = toupper(*it);

  switch( first ) {
  case 'E':
  case 'D':
    ++position; ++it;
    switch( *it ){
    case '-':
      sign = -1;
    case '+':
      boundCheck( position );
      ++position; ++it;
    default: break;
    }
    break;
  case '-':
    sign = -1;
  case '+':
    ++position; ++it;
    break;
  default:
    return 0;
  }

  if ( unlikely( not isdigit( *it ) ) ){
    throw std::runtime_error
      ("illegal character encountered while parsing real number exponent");
  }

  uint64_t exponent = 0;
  do {
    exponent = 10 * exponent + ( *it - 48 );
    if ( position == Real::endPosition ){ break; }
    ++position; ++it;
  } while ( isdigit( *it ) );

  return sign * exponent;
}
