#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Character read", "[Character], [read]"){
  {
    std::vector< std::pair< std::string, std::string > >
      testSet = { { "Lorem ipsum", "Lorem ipsum" },
                  { "Lorem ipsum dolor sit amet", "Lorem ipsum" },
                  { "Lorem\n", "Lorem      " } };
    for ( auto& pair : testSet ){
      auto it = pair.first.begin();
      auto end = pair.first.end();
      auto string = disco::Character< 11 >::read( it, end );
      REQUIRE( string == pair.second );
    }
  }
  {
    std::vector< std::pair< std::string, char > >
      testSet = { { "Lorem ipsum0", '0' },
                  { "Lorem\n", '\n' } };
    for ( auto& pair : testSet ){
      auto it = pair.first.begin();
      auto end = pair.first.end();
      disco::Character< 11 >::read( it, end );
      REQUIRE( *it == pair.second );
    }
  }
  
}
