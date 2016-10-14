template< typename Iterator >
static int64_t
parseInteger( Iterator& it, uint16_t remainingCharacters, Signed ){
  int64_t sign = 1;
  if ( ( *it == '-' ) || ( *it == '+' ) ){
    if ( --remainingCharacters == 0 ){ throw std::exception(); }
    sign -= ( *it == '-' ) * 2;
    ++it;
  }
  return sign * int64_t( parseInteger( it, remainingCharacters, Unsigned() ) );
}

template< typename Iterator >
static uint64_t
parseInteger( Iterator& it, uint16_t remainingCharacters, Unsigned ){
  uint64_t x = 0;
  while ( remainingCharacters--
          and not ( FixedWidthField_::isNewline( *it )
                    or FixedWidthField_::isEOF( *it ) ) ){
    if( not std::isdigit( *it ) ){
      throw std::runtime_error("Bad value during integer read");
    }
    x = x * 10 + ( *it - '0');		
    ++it;
  }
  return x;
}
