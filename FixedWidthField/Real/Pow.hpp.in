namespace disco {

template< typename T, typename Integer >
constexpr T pow( T real, Integer power ){
  return
    ( power < 0 )  ? 1.0 / pow( real, -power ) :
    ( power == 0 ) ? 1.0 :
    ( power == 1 ) ? real :
    ( ( power % 2 ) == 0 ) ? pow( real * real , power / 2 ) :
                             real * pow( real, power - 1 );
}

}
