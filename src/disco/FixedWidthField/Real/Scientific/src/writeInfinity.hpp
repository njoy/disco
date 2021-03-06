template< typename Iterator >
static void
writeInfinity( Iterator& it, bool isNegative, typename Real_t::Full ){
  auto remainingBlanks = w - 8;
  while ( --remainingBlanks > 0 ){
    *it++ = ' ';
  }
  if ( isNegative ){
    *it++ = '-'; 
  } else if ( remainingBlanks == 0 ) {
    *it++ = ' ';
  }
  *it++ = 'I';
  *it++ = 'n';
  *it++ = 'f';
  *it++ = 'i';
  *it++ = 'n';
  *it++ = 'i';
  *it++ = 't';
  *it++ = 'y';
}

template< typename Iterator >
static void
writeInfinity( Iterator& it, bool isNegative, typename Real_t::Partial ){
  auto remainingBlanks = int(w) - 3;
  if (  (remainingBlanks - isNegative) < 0 ){
    writeInvalid( it );
    return;
  }
  while ( --remainingBlanks > 0 ){
    *it++ = ' ';
  }
  if ( isNegative ){
    *it++ = '-'; 
  } else if ( remainingBlanks == 0 ){
    *it++ = ' ';
  }
  *it++ = 'I';
  *it++ = 'n';
  *it++ = 'f';
}

template< typename Iterator >
static void
writeInfinity
( Iterator& it, bool isNegative, typename Real_t::PartialNegative ){
  isNegative ?
    writeInfinity( it, isNegative, typename Real_t::Partial() ) :
    writeInfinity( it, isNegative, typename Real_t::Full() );
}
