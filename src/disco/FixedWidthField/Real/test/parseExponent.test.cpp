#include <string>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO( "Real - parse exponent" ) {

  auto parse = [] ( const std::string string, uint16_t& position ) {

    auto iter = string.begin();
    position = 0;
    return njoy::disco::Real< 6 >::parseExponent( iter, position );
  };

  THEN( "valid exponent strings can be read up to the correct position" )
  {
    uint16_t position = 0;

    CHECK( +123 == parse( "+123", position ) );
    CHECK( 4 == position );
    CHECK( +123 == parse( "+ 123", position ) );
    CHECK( 5 == position );
    CHECK( +123 == parse( "E+123", position ) );
    CHECK( 5 == position );
    CHECK( +123 == parse( "E+ 123", position ) );
    CHECK( 6 == position );
    CHECK( +123 == parse( "E123", position ) );
    CHECK( 4 == position );
    CHECK( +123 == parse( "E 123", position ) );
    CHECK( 5 == position );
    CHECK( +123 == parse( "e+123", position ) );
    CHECK( 5 == position );
    CHECK( +123 == parse( "e+ 123", position ) );
    CHECK( 6 == position );
    CHECK( +123 == parse( "e123", position ) );
    CHECK( 4 == position );
    CHECK( +123 == parse( "e 123", position ) );
    CHECK( 5 == position );
    CHECK( +123 == parse( "D+123", position ) );
    CHECK( 5 == position );
    CHECK( +123 == parse( "D+ 123", position ) );
    CHECK( 6 == position );
    CHECK( +123 == parse( "D123", position ) );
    CHECK( 4 == position );
    CHECK( +123 == parse( "D 123", position ) );
    CHECK( 5 == position );
    CHECK( +123 == parse( "d+123", position ) );
    CHECK( 5 == position );
    CHECK( +123 == parse( "d+ 123", position ) );
    CHECK( 6 == position );
    CHECK( +123 == parse( "d123", position ) );
    CHECK( 4 == position );
    CHECK( +123 == parse( "d 123", position ) );
    CHECK( 5 == position );

    CHECK( -123 == parse( "-123", position ) );
    CHECK( 4 == position );
    CHECK( -123 == parse( "- 123", position ) );
    CHECK( 5 == position );
    CHECK( -123 == parse( "E-123", position ) );
    CHECK( 5 == position );
    CHECK( -123 == parse( "E- 123", position ) );
    CHECK( 6 == position );
    CHECK( -123 == parse( "e-123", position ) );
    CHECK( 5 == position );
    CHECK( -123 == parse( "e- 123", position ) );
    CHECK( 6 == position );
    CHECK( -123 == parse( "D-123", position ) );
    CHECK( 5 == position );
    CHECK( -123 == parse( "D- 123", position ) );
    CHECK( 6 == position );
    CHECK( -123 == parse( "d-123", position ) );
    CHECK( 5 == position );
    CHECK( -123 == parse( "d- 123", position ) );
    CHECK( 6 == position );

    // exponent is only read up to the first non-digit
    CHECK( +123 == parse( "+123 ", position ) );
    CHECK( 4 == position );
    CHECK( +123 == parse( "+123a", position ) );
    CHECK( 4 == position );
  }

  THEN( "invalid exponent strings cause an exception" )
  {
    uint16_t position = 0;

    CHECK_THROWS( parse( "-a123", position ) );
    CHECK_THROWS( parse( "+a123", position ) );
    CHECK_THROWS( parse( "E-a123", position ) );
    CHECK_THROWS( parse( "E+a123", position ) );
    CHECK_THROWS( parse( "D-a123", position ) );
    CHECK_THROWS( parse( "D+a123", position ) );
    CHECK_THROWS( parse( "E -123", position ) );
    CHECK_THROWS( parse( "E +123", position ) );
    CHECK_THROWS( parse( "D -123", position ) );
    CHECK_THROWS( parse( "D +123", position ) );

    CHECK_THROWS( parse( "-  a3", position ) );
    CHECK_THROWS( parse( "-    ", position ) );
    CHECK_THROWS( parse( "+  a3", position ) );
    CHECK_THROWS( parse( "+    ", position ) );
  }
}
