template< typename T, typename Iterator, bool trust = true >
static T
read( Iterator& it, const Iterator& end ){
  using Signedness =
    std::conditional_t< std::is_signed< T >::value, Signed, Unsigned >;
  
  FixedWidthField_::verifyWidth_( it, end, TrustTag< trust >() );
  auto position = FixedWidthField_::skipPad( it );

  if ( position == w
       or FixedWidthField_::isNewline( *it )
       or FixedWidthField_::isEOF( *it ) ){ return T(0); }
  
  auto remainingCharacters = ( w - position );

  auto result = parseInteger( it, remainingCharacters, Signedness() );
  if ( result < std::numeric_limits< T >::min() ){
    throw std::runtime_error("Value overflowed during integer read");
  } else if ( result > std::numeric_limits< T >::max() ){
    throw std::runtime_error("Value overflowed during integer read");
  }
  return static_cast< T >( result );
}

template< typename Iterator, bool trust = true >
static int
read( Iterator& it, const Iterator& end ){
  return read< int >( it, end );
}
