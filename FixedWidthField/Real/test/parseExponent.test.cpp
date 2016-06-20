#include <string>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Real parse exponent", "[Real], [parseExponent]"){
  std::vector< std::string >
    test_strings{ {"+123"}, {"-123"},
                  {"E123"}, {"E+123"}, {"E-123"},
                  {"e123"}, {"e+123"}, {"e-123"},
                  {"D123"}, {"D+123"}, {"D-123"},
                  {"d123"}, {"d+123"}, {"d-123"} };
  uint16_t p = 0;
  bool success;
  for (unsigned i = 0; i < test_strings.size(); ++i){
    p = 0; auto si = test_strings[i].begin();
    if ( (i + 1) % 3 == 2 ){
      REQUIRE( -123 == disco::Real<5>::parseExponent( si, p ) );
    } else {
      REQUIRE( 123 == disco::Real<5>::parseExponent( si, p ) );
    }
  }
}
