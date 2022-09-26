#include <string>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO( "Real - parse fraction" ) {

  auto parse = [] ( const std::string string,
                    uint16_t& position, bool& success ) {

    position = 0;
    success = false;
    auto iter = string.begin();
    return njoy::disco::Real< 6 >::parseFraction( iter, position, success );
  };

  THEN( "valid fraction strings can be read up to the correct position" ) {

    uint16_t position = 0;
    bool success = false;

    CHECK( 123 == parse( ".123", position, success ) );
    CHECK( success == true );
    CHECK( position == 4 );
    CHECK( 123 == parse( ".123E", position, success ) );
    CHECK( success == true );
    CHECK( position == 4 );
    CHECK( 123 == parse( ".123 E", position, success ) );
    CHECK( success == true );
    CHECK( position == 4 );
  }

  THEN( "a fraction value cannot be read if the string does not start with "
        "a decimal point" ) {

    uint16_t position = 0;
    bool success = false;

    CHECK( 0 == parse( " .123", position, success ) );
    CHECK( success == false );
    CHECK( position == 0 );
    CHECK( 0 == parse( "a123", position, success ) );
    CHECK( success == false );
    CHECK( position == 0 );
    CHECK( 0 == parse( "123", position, success ) );
    CHECK( success == false );
    CHECK( position == 0 );
    CHECK( 0 == parse( ".   E", position, success ) );
    CHECK( success == false );
    CHECK( position == 1 );
  }
}
