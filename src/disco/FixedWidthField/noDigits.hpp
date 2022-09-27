template< typename Integer >
constexpr int noDigits( Integer i ) {
  
  return ( i < 10 ) ? 1 : 1 + noDigits( i / 10 );
}
