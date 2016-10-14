template< typename Iterator >
static bool
parseInfinity( Iterator& it, uint16_t& position ){
  auto canProceed = [&it](){
    return not ( FixedWidthField_::isNewline(*it)
                 or FixedWidthField_::isEOF(*it) );
  };
  const auto remainingWidth = int(w) - position;
  switch ( remainingWidth ){
  case 3:
    position += 3;
    return ( toupper( *it++ ) == 'I' )
           && ( canProceed() && toupper( *it++ ) == 'N' )
           && ( canProceed() && toupper( *it++ ) == 'F' );
  case 8:
    position += 8;
    return ( toupper( *it++ ) == 'I' )
           && ( canProceed() && toupper( *it++ ) == 'N' )
           && ( canProceed() && toupper( *it++ ) == 'F' )
           && ( canProceed() && toupper( *it++ ) == 'I' )
           && ( canProceed() && toupper( *it++ ) == 'N' )
           && ( canProceed() && toupper( *it++ ) == 'I' )
           && ( canProceed() && toupper( *it++ ) == 'T' )
           && ( canProceed() && toupper( *it++ ) == 'Y' );
  default:
    return false;
  }
}