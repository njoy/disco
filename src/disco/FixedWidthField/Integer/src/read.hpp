template< typename T, typename Iterator, bool trust = true >
static T
read( Iterator& it, const Iterator& ){
  using Signedness =
    std::conditional_t< std::is_signed< T >::value, Signed, Unsigned >;

  auto position = FixedWidthField_::whiteSpace( it );

  if( FixedWidthField_::isNewline(*it, it) or FixedWidthField_::isEOF(*it) ){
    return T(0);
  }

  if ( position == w ){
    ++it;
    return T(0);
  }

  auto result = parseInteger( it, position, Signedness() );
  if ( unlikely( result < std::numeric_limits< T >::min()
                 or result > std::numeric_limits< T >::max() ) ){
    throw std::runtime_error("Value overflowed during integer read");
  }

  std::advance( it, not ( ( position == w )
                          or FixedWidthField_::isNewline( *it, it )
                          or FixedWidthField_::isEOF( *it ) ) );

  if ( unlikely( not FixedWidthField_::whiteSpace( it, position ) ) ){
    throw std::runtime_error("Bad value during integer read");
  }
  return static_cast< T >( result );
}

template< typename Iterator, bool trust = true >
static int
read( Iterator& it, const Iterator& end ){
  return read< int >( it, end );
}
