template< typename Iterator >
static int16_t parseSign( Iterator& it, uint16_t& position ){
  switch ( *it ){
  case '+': ++it; ++position; return 1;
  case '-': ++it; ++position; return -1;
  default: return 1;
  }
}
