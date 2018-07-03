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
formatUnpadded( Type<short int> ){ return "%*hi"; }

static constexpr const char*
formatPadded( Type<short int> ){ return "%0*hi"; }

static constexpr const char*
formatUnpadded( Type<unsigned short int> ){ return "%*hu"; }

static constexpr const char*
formatPadded( Type<unsigned short int> ){ return "%0*hu"; }

static constexpr const char*
formatUnpadded( Type<int> ){ return "%*i"; }

static constexpr const char*
formatPadded( Type<int> ){ return "%0*i"; }

static constexpr const char*
formatUnpadded( Type<unsigned int> ){ return "%*u"; }

static constexpr const char*
formatPadded( Type<unsigned int> ){ return "%0*u"; }

static constexpr const char*
formatUnpadded( Type<long> ){ return "%*ld"; }

static constexpr const char*
formatPadded( Type<long> ){ return "%0*ld"; }

static constexpr const char*
formatUnpadded( Type<unsigned long> ){ return "%*lu"; }

static constexpr const char*
formatPadded( Type<unsigned long> ){ return "%0*lu"; }

static constexpr const char*
formatUnpadded( Type<long long> ){ return "%*lld"; }

static constexpr const char*
formatPadded( Type<long long> ){ return "%0*lld"; }

static constexpr const char*
formatUnpadded( Type<unsigned long long> ){ return "%*llu"; }

static constexpr const char*
formatPadded( Type<unsigned long long> ){ return "%0*llu"; }

template< typename Representation, typename Iterator >
static void
write( Representation integer, Iterator& it, WithoutPadding ){
  auto tag = std::is_signed< Representation >();
  const auto noDigits = disco::noDigits( uint64_t( abs( integer, tag ) ) )
                        + ( integer < 0 );
  if ( noDigits > w ){ writeInvalid( it ); return; }
  std::array< char, w+1  > buffer;
  int consumedCharacters =
    snprintf( &buffer[0], w+1,
              formatUnpadded( type_c<Representation> ), w, integer );
  if (consumedCharacters != w){ throw std::exception(); }
  auto begin = buffer.begin();
  auto end = begin + w;
  while ( begin != end ) { *it++ = *begin++; }
}

template< typename Representation, typename Iterator >
static void
write( Representation integer, Iterator& it, WithPadding ){
  auto tag = std::is_signed< Representation >();
  const auto noDigits = disco::noDigits( uint64_t( abs( integer, tag ) ) )
                        + ( integer < 0 );
  if ( noDigits > w ){ writeInvalid( it ); return; }
  auto remainingNonblanks = ( noDigits > m ) ? noDigits : m;
  auto remainingBlanks = w - remainingNonblanks;
  while( remainingBlanks-- ){ *it++ = ' '; }
  std::array< char, w+1  > buffer;
  int consumedCharacters =
    snprintf( &buffer[0], remainingNonblanks + 1,
              formatPadded( type_c< Representation > ),
              remainingNonblanks, integer );
  if (consumedCharacters != remainingNonblanks){ throw std::exception(); }
  auto begin = buffer.begin();
  auto end = begin + remainingNonblanks;
  while ( begin != end ) { *it++ = *begin++; }
}


