template< typename UnsignedInteger >
static uint16_t
noDigits( UnsignedInteger mantissa ){
  if ( mantissa < 10ull ){ return 1; };
  if ( mantissa < 100ull ){ return 2; };
  if ( mantissa < 1000ull ){ return 3; };
  if ( mantissa < 10000ull ){ return 4; };
  if ( mantissa < 100000ull ){ return 5; };
  if ( mantissa < 1000000ull ){ return 6; };
  if ( mantissa < 10000000ull ){ return 7; };
  if ( mantissa < 100000000ull ){ return 8; };
  if ( mantissa < 1000000000ull ){ return 9; };
  if ( mantissa < 10000000000ull ){ return 10; };
  if ( mantissa < 100000000000ull ){ return 11; };
  if ( mantissa < 1000000000000ull ){ return 12; };
  if ( mantissa < 10000000000000ull ){ return 13; };
  if ( mantissa < 100000000000000ull ){ return 14; };
  if ( mantissa < 1000000000000000ull ){ return 15; };
  if ( mantissa < 10000000000000000ull ){ return 16; };
  if ( mantissa < 100000000000000000ull ){ return 17; };
  if ( mantissa < 1000000000000000000ull ){ return 18; };
  if ( mantissa < 10000000000000000000ull ){ return 19; };
  return 20;
}
