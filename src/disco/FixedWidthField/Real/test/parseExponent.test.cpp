#include <iterator>
#include <string>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO( "Real parse exponent" ) {

  auto parse = [] ( const std::string string ) {

    auto iter = string.begin();
    uint16_t position = 0;
    return njoy::disco::Real<6>::parseExponent( iter, position );
  };

  THEN( "valid exponent strings can be read" )
  {
    CHECK( +123 == parse( "+123" ) );
    CHECK( +123 == parse( "+ 123" ) );
    CHECK( +123 == parse( "E+123" ) );
    CHECK( +123 == parse( "E+ 123" ) );
    CHECK( +123 == parse( "E123" ) );
    CHECK( +123 == parse( "E 123" ) );
    CHECK( +123 == parse( "e+123" ) );
    CHECK( +123 == parse( "e+ 123" ) );
    CHECK( +123 == parse( "e123" ) );
    CHECK( +123 == parse( "e 123" ) );
    CHECK( +123 == parse( "D+123" ) );
    CHECK( +123 == parse( "D+ 123" ) );
    CHECK( +123 == parse( "D123" ) );
    CHECK( +123 == parse( "D 123" ) );
    CHECK( +123 == parse( "d+123" ) );
    CHECK( +123 == parse( "d+ 123" ) );
    CHECK( +123 == parse( "d123" ) );
    CHECK( +123 == parse( "d 123" ) );

    CHECK( -123 == parse( "-123" ) );
    CHECK( -123 == parse( "- 123" ) );
    CHECK( -123 == parse( "E-123" ) );
    CHECK( -123 == parse( "E- 123" ) );
    CHECK( -123 == parse( "e-123" ) );
    CHECK( -123 == parse( "e- 123" ) );
    CHECK( -123 == parse( "D-123" ) );
    CHECK( -123 == parse( "D- 123" ) );
    CHECK( -123 == parse( "d-123" ) );
    CHECK( -123 == parse( "d- 123" ) );
  }

  THEN( "invalid exponent strings cause an exception" )
  {
    CHECK_THROWS( parse( "--123" ) );
    CHECK_THROWS( parse( "-+123" ) );
    CHECK_THROWS( parse( "++123" ) );
    CHECK_THROWS( parse( "+-123" ) );
    CHECK_THROWS( parse( "E--123" ) );
    CHECK_THROWS( parse( "E-+123" ) );
    CHECK_THROWS( parse( "E++123" ) );
    CHECK_THROWS( parse( "E+-123" ) );
    CHECK_THROWS( parse( "D--123" ) );
    CHECK_THROWS( parse( "D-+123" ) );
    CHECK_THROWS( parse( "D++123" ) );
    CHECK_THROWS( parse( "D+-123" ) );
    CHECK_THROWS( parse( "E -123" ) );
    CHECK_THROWS( parse( "E +123" ) );
    CHECK_THROWS( parse( "E +123" ) );
    CHECK_THROWS( parse( "E -123" ) );
    CHECK_THROWS( parse( "D -123" ) );
    CHECK_THROWS( parse( "D +123" ) );
    CHECK_THROWS( parse( "D +123" ) );
    CHECK_THROWS( parse( "D -123" ) );

    CHECK_THROWS( parse( "-  a3" ) );
    CHECK_THROWS( parse( "-    " ) );
  }
}
