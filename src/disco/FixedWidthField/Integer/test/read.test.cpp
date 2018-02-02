#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Integer read", "[Integer], [read]"){
  std::string blank {"          "};
  auto begin = blank.begin();
  auto end = blank.end();
  auto result = njoy::disco::Integer<10>::read<int>(begin, end);
  REQUIRE( result == 0 );
  REQUIRE( end - begin == 0 );

  std::string shortEntry {"       \n"};
  begin = shortEntry.begin();
  end = shortEntry.end();
  result = njoy::disco::Integer<10>::read<int>(begin, end);
  REQUIRE( result == 0 );
  REQUIRE( *begin == '\n' );
  REQUIRE( end - begin  == 1 );

  std::string invalid = " a";
  begin = invalid.begin();
  end = invalid.end();
  REQUIRE_THROWS( njoy::disco::Integer<2>::read< int >(begin, end) );

  const std::unordered_map
    < int, std::vector< std::string > > valid =
    {{    0, { "         0",
               "        +0",
               "        -0",
               "0000000000",
               "  00000000",
               "    000000",
               "     -0000",
               "0         ",
               "+0        ",
               "-0        ",
               "00000000  ",
               "     0    ",
               "    +0    ",
               "    -0    ",
               " 00000000 " }},
     {    1, { "         1",
               "        +1",
               "        01",
               "  +0000001",
               "1         ",
               "+1        ",
               "01        ",
               "+0000001  ",
               "     1    ",
               "    +1    ",
               " +0000001 " }},
     {   -1, { "        -1",
               "       -01",
               "      -001",
               "  -0000001",
               "-1        ",
               "-01       ",
               "-001      ",
               "-0000001  "}},
     { 2147483647,
             { "2147483647"}}};

  for ( auto& number : valid ){
    for ( auto& string : number.second ){
      auto begin = string.begin();
      auto end = string.end();
      auto result = njoy::disco::Integer<10>::read< int >(begin, end);
      REQUIRE( number.first == result );
      REQUIRE( end - begin == 0 );
    }
  }
  std::string TooLarge = "2147483648";
  begin = TooLarge.begin();
  end = TooLarge.end();
  REQUIRE_THROWS( njoy::disco::Integer<10>::read< int >(begin, end) );

  std::string TooSmall = "-2147483649";
  begin = TooSmall.begin();
  end = TooSmall.end();
  REQUIRE_THROWS( njoy::disco::Integer<11>::read< int >(begin, end) );
}
