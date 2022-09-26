#include <string>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO( "Real - parse base" ) {

  auto parse = [] ( const std::string string,
                    uint16_t& position, bool& success ) {

    position = 0;
    success = false;
    auto iter = string.begin();
    return njoy::disco::Real< 5 >::parseBase( iter, position, success );
  };

  THEN( "valid base strings can be read up to the correct position" ) {

    uint16_t position = 0;
    bool success = false;

    CHECK( 123 == parse( "123", position, success ) );
    CHECK( success == true );
    CHECK( position == 3 );
    CHECK( 123 == parse( "123.", position, success ) );
    CHECK( success == true );
    CHECK( position == 3 );
    CHECK( 123 == parse( "123.000", position, success ) );
    CHECK( success == true );
    CHECK( position == 3 );
    CHECK( 123 == parse( "123 ", position, success ) );
    CHECK( success == true );
    CHECK( position == 3 );
  }

  THEN( "a base value cannot be read if the string has no base value" ) {

    uint16_t position = 0;
    bool success = false;

    CHECK( 0 == parse( ".123", position, success ) );
    CHECK( success == false );
    CHECK( position == 0 );
    CHECK( 0 == parse( "a123", position, success ) );
    CHECK( success == false );
    CHECK( position == 0 );
  }
}
