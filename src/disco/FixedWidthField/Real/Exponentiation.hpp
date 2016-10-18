template< typename Representation, int length, int offset >
constexpr auto generateCache(){
  std::array< Representation, length > partialCache{};
  auto hackIterator = &( std::get<0>(partialCache) );
  for ( int index = 0; index < length; ++index ){
    *hackIterator++  = njoy::disco::pow( Representation(10), index - offset );
  }
  return partialCache;
}

template< typename Representation, int length, int offset >
constexpr auto cachedPowers = generateCache< Representation, length, offset >();

template< typename Representation, int length  >
struct Exponentation {
  static constexpr int
  offset = std::is_integral<Representation>::value ? 0 : 1 + length / 2;
  
  static constexpr Representation
  cache( int power ){
    return cachedPowers< Representation, length, offset >[power + offset];
  }
};

template< typename Representation >
using realExponentiation = Exponentation< Representation, 615 >;

template< typename Representation >
constexpr int
maxOrder = noDigits( std::numeric_limits< Representation >::max() ) - 1;

template< typename Representation >
using integerExponentiation =
  Exponentation< Representation, maxOrder<Representation> >;
