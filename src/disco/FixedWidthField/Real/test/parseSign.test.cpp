#include <string>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Real parse sign", "[Real], [parseSign]"){
  std::vector< std::string >
    test_strings{ {" 123."}, {"+123."}, {"-123."} };
  std::vector< int >
    signs = { 1, 1, -1 };
  for (unsigned i = 0; i < signs.size(); ++i){
    uint16_t p = 0u;
    auto si = test_strings[i].begin();
    REQUIRE( signs[i] == njoy::disco::Real<5>::parseSign( si, p ) );
  }
}
