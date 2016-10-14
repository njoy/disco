#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Character write", "[Character], [write]"){
  {
    std::vector< std::pair< std::string, std::string > >
      testSet = { { "Lorem ipsum", "Lorem ipsum" },
                  { "Lorem ipsum dolor sit amet", "Lorem ipsum" },
                  { "Lorem", "      Lorem" } };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::Character< 11 >::write( pair.first, it );
      REQUIRE(buffer == pair.second);
    }
    std::string buffer("");
    auto it = std::back_inserter(buffer);
    disco::Character< 11 >::write( it );
    REQUIRE(buffer == "           ");
  }
}
