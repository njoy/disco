template< typename Iterator >
static uint64_t
parseInteger( Iterator& it, uint16_t& position, Unsigned ){
  uint64_t x = 0;
  uint64_t safety = 0;
  while ( position < w and std::isdigit( *it ) ){
    safety = x * 10 + ( *it - '0' );

    if ( unlikely( safety < x ) ){
      throw std::runtime_error("Value overflowed during integer read");
    }

    x = safety;
    ++it;
    ++position;
  }
  return x;
}

template< typename Iterator >
static int64_t
parseInteger( Iterator& it, uint16_t& position, Signed ){
  int64_t sign = 1;

  if ( ( *it == '-' ) or ( *it == '+' ) ){
    if ( unlikely( ++position == w ) ){
      throw std::runtime_error("only sign found in integer field");
    }
    sign = 44 - *it;
    ++it;
  }

  const auto magnitude = parseInteger( it, position, Unsigned() );

  if ( unlikely( magnitude > std::numeric_limits< int64_t >::max() ) ){
    throw std::runtime_error( "Value overflowed during integer read" );
  }

  return sign * int64_t( magnitude );
}
