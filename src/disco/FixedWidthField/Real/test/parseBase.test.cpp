#include <string>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Real parse base", "[Real], [parseBase]"){
  std::vector< std::string >
    test_strings{ {"123"}, {"123."}, {"123.000"} };
  uint16_t p;
  bool success;
  for (unsigned i = 0; i < test_strings.size(); ++i){
    p = 0;
    auto si = test_strings[i].begin();
    REQUIRE( 123 == njoy::disco::Real<5>::parseBase( si, p, success ) );
    REQUIRE( success == true );
    REQUIRE( p == 3 );
  }

  std::string baseless(".123");
  p = 0;
  auto si = baseless.begin();
  njoy::disco::Real<5>::parseBase( si, p, success );
  REQUIRE( p == 0 );
  REQUIRE( success == false );
}
