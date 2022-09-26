#include <string>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO( "Real - parse sign" ) {

  auto parse = [] ( const std::string string, uint16_t& position ) {

    position = 0;
    auto iter = string.begin();
    return njoy::disco::Real< 5 >::parseSign( iter, position );
  };

  THEN( "valid sign strings can be read up to the correct position" )
  {
    uint16_t position = 0;

    CHECK( +1 == parse( "123", position ) );
    CHECK( 0 == position );
    CHECK( +1 == parse( "+123", position ) );
    CHECK( 1 == position );
    CHECK( -1 == parse( "-123", position ) );
    CHECK( 1 == position );
  }
}
