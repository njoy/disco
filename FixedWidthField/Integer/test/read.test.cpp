#include <string>
#include <unordered_map>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Integer read", "[Integer], [read]"){
  const std::unordered_map
    < int, std::vector< std::string > > valid =
    {{    0, { "          ", "         0", "        +0", "        -0",
               "0000000000", "  00000000", "    000000", "     -0000"}},
     {    1, { "         1", "        +1", "        01", "  +0000001"}}, 
     {   -1, { "        -1", "       -01", "      -001", "  -0000001"}},
     { 2147483647,         { "2147483647"}}};
  for ( auto& number : valid ){
    for ( auto& string : number.second ){
      auto begin = string.begin();
      auto end = string.end();
      auto result = disco::Integer<10>::read< int >(begin, end);
      REQUIRE( number.first == result );
    }
  }
  std::string TooLarge = "2147483648";
  auto begin = TooLarge.begin();
  auto end = TooLarge.end();
  REQUIRE_THROWS( disco::Integer<10>::read< int >(begin, end) );

  std::string TooSmall = "-2147483649";
  begin = TooSmall.begin();
  end = TooSmall.end();
  REQUIRE_THROWS( disco::Integer<11>::read< int >(begin, end) );
}
