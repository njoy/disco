#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("FixedPoint write", "[FixedPoint], [write]"){
  {
    std::vector< std::pair< double, std::string > >
      testSet = { { 0.0, "     0.0000" },
                  { 10.0, "    10.0000" },
                  { 3.14159, "     3.1416"},
                  { std::numeric_limits<double>::infinity(), "   Infinity"},
                  { 0.69314718056, "     0.6931"},
                  { 1E-100, "     0.0000" },
                  { 1E6 - 1, "999999.0000" },
                  { 1E6,     "***********" },
                  { -(1E5 - 1), "-99999.0000" },
                  { -1E5,     "***********" } };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::FixedPoint< 11, 4 >::write( pair.first, it );
      REQUIRE(buffer == pair.second);
    }
  }
}
