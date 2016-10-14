template< typename Representation >
static Representation
abs( Representation integer, std::true_type ){
  return integer < 0 ? -integer : integer;
}

template< typename Representation >
static Representation
abs( Representation integer, std::false_type ){
  return integer;
}

static constexpr const char*
formatUnpadded( std::true_type ){ return "%*i"; }

static constexpr const char*
formatUnpadded( std::false_type ){ return "%*u"; }

static constexpr const char*
formatPadded( std::true_type ){ return "%0*i"; }

static constexpr const char*
formatPadded( std::false_type ){ return "%0*u"; }

template< typename Representation, typename Iterator >
static void
write( Representation integer, Iterator& it, WithoutPadding ){
  auto tag = std::is_signed< Representation >();
  const auto noDigits = Real< 0 >::noDigits( uint64_t( abs( integer, tag ) ) )
                        + ( integer < 0 );
  if ( noDigits > w ){ Scientific< w, 0 >::writeInvalid( it ); return; }
  std::array< char, w+1  > buffer;
  int consumedCharacters = snprintf( &buffer[0], w+1,
                                     formatUnpadded( tag ), w, integer );
  if (consumedCharacters != w){ throw std::exception(); }
  auto begin = buffer.begin();
  auto end = begin + w;
  while ( begin != end ) { *it++ = *begin++; }
}

template< typename Representation, typename Iterator >
static void
write( Representation integer, Iterator& it, WithPadding ){
  auto tag = std::is_signed< Representation >();
  const auto noDigits = Real< 0 >::noDigits( uint64_t( abs( integer, tag ) ) )
                        + ( integer < 0 );
  if ( noDigits > w ){ Scientific< w, 0 >::writeInvalid( it ); return; }
  auto remainingNonblanks = ( noDigits > m ) ? noDigits : m;
  auto remainingBlanks = w - remainingNonblanks;
  while( remainingBlanks-- ){ *it++ = ' '; }
  std::array< char, w+1  > buffer;
  int consumedCharacters =
    snprintf( &buffer[0], remainingNonblanks + 1,
              formatPadded( tag ), remainingNonblanks, integer );
  if (consumedCharacters != remainingNonblanks){ throw std::exception(); }
  auto begin = buffer.begin();
  auto end = begin + remainingNonblanks;
  while ( begin != end ) { *it++ = *begin++; }
}


