template< typename Representation, typename Iterator, bool trust = true >
static Representation
read( Iterator& it, const Iterator& ){
  static_assert( std::is_same< Representation, std::string >::value,
                 "Character strings are only defined for std::string" );
  std::string characterString;
  characterString.reserve(w);
  auto remainingCharacters = w;
  while( remainingCharacters--
         and not ( FixedWidthField_::isEOF( *it )
		   or FixedWidthField_::isNewline( *it, it ) ) ){
    characterString.push_back( *it++ );
  }
  ++remainingCharacters;
  while( remainingCharacters-- ){ characterString.push_back( ' ' );  }
  return characterString;
}

template< typename Iterator, bool trust = true >
static std::string
read( Iterator& it, const Iterator& end ){
  return read< std::string >( it, end );
}
