#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("FixedPoint write", "[FixedPoint], [write]"){
  {
    std::vector< std::pair< double, std::string > >
      testSet = { { 0.0, " 0.000000+0" }, 
                  { 10.0, " 1.000000+1" },
                  { 3.14159, " 3.141590+0"},
                  { std::numeric_limits<double>::infinity(), "   Infinity"},
                  { 0.69314718056, " 6.931472-1"},
                  { 1E-100, "***********" },
                  { 1E10, " 1.00000+10" },
                  { 1E-10, " 1.00000-10" },
                  { -1E10, "-1.00000+10" },
                  { -1E-10, "-1.00000-10" },
                  { -10.0, "-1.000000+1" },
                  { -3.14159, "-3.141590+0"},
                  { -std::numeric_limits<double>::infinity(), "  -Infinity"},
                  { -0.69314718056, "-6.931472-1"} };

    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::ENDF::write( pair.first, it );
      REQUIRE(buffer == pair.second);
    }
  }
}
