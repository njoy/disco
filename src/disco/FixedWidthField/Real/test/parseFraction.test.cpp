#include <string>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Real parse fraction", "[Real], [parseFraction]"){
  std::vector< std::string > test_strings{ {".123"}, {".123E"} };
  uint16_t p = 0;
  bool success;
  for (unsigned i = 0; i < test_strings.size(); ++i){
    p = 0; auto si = test_strings[i].begin();
    REQUIRE( 123 == njoy::disco::Real<5>::parseFraction( si, p, success ) );
    REQUIRE( success == true );
  }
  REQUIRE( p == 4 );
  
  std::string fractionless("123");
  p = 0;
  auto si = fractionless.begin();
  njoy::disco::Real<5>::parseFraction( si, p, success );
  REQUIRE( p == 0 );
  REQUIRE( success == false );
}

