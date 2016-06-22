#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Scientific write", "[Scientific], [write]"){
  {
    std::vector< std::pair< double, std::string > >
      testSet = { { 0.0, " 0.0000E+00" },
                  { 10.0, " 1.0000E+01" },
                  { 3.14159, " 3.1416E+00"},
                  { std::numeric_limits<double>::infinity(), "   Infinity"},
                  { 0.69314718056, " 6.9315E-01"},
                  { 1E-100, " 1.0000-100"} };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::Scientific< 11, 4 >::write( pair.first, it );
      REQUIRE(buffer == pair.second);
    }
  }
  {
    std::vector< std::pair< double, std::string > >
      testSet = { { 0.0, " 0.0000E+00" },
                  { 10.0, " 1.0000E+01" },
                  { 3.14159, " 3.1416E+00"},
                  { std::numeric_limits<double>::infinity(), "   Infinity"},
                  { 0.69314718056, " 6.9315E-01"},
                  { 1E-100, "***********"} };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::Scientific< 11, 4, 2 >::write( pair.first, it );
      REQUIRE(buffer == pair.second);
    }
  }
  {
    std::vector< std::pair< double, std::string > >
      testSet = { { 0.0, "  0.0000E+0" },
                  { 10.0, "  1.0000E+1" },
                  { 3.14159, "  3.1416E+0"},
                  { std::numeric_limits<double>::infinity(), "   Infinity"},
                  { 0.69314718056, "  6.9315E-1"},
                  { 1E-100, "***********"} };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::Scientific< 11, 4, 1 >::write( pair.first, it );
      REQUIRE(buffer == pair.second);
    }
  }
  {
    std::vector< std::pair< double, std::string > >
      testSet = { { 0.0, "0.0000E+000" },
                  { 10.0, "1.0000E+001" },
                  { 3.14159, "3.1416E+000"},
                  { std::numeric_limits<double>::infinity(), "   Infinity"},
                  { 0.69314718056, "6.9315E-001"},
                  { 1E-100, "1.0000E-100"} };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::Scientific< 11, 4, 3 >::write( pair.first, it );
      REQUIRE(buffer == pair.second);
    }
  }
  {
    std::vector< std::pair< double, std::string > >
      testSet = { { 0.0, "0.0000E+000" },
                  { 10.0, "1.0000E+001" },
                  { 3.14159, "3.1416E+000"},
                  { std::numeric_limits<double>::infinity(), "   Infinity"},
                  { 0.69314718056, "6.9315E-001"},
                  { 1E-100, "1.0000E-100"} };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::Scientific< 11, 4, 3 >::write( pair.first, it );
      disco::Scientific< 11, 4, 3 >::write( 10.0, it );
      REQUIRE( buffer == ( pair.second + "1.0000E+001" ) );
    }
  }
  {
    std::vector< std::pair< double, std::string > >
      testSet = { { 0.0, " 0.0000E+00" },
                  { 10.0, " 1.0000E+01" },
                  { 3.14159, " 3.1416E+00"},
                  { std::numeric_limits<double>::infinity(), "   Infinity"},
                  { 0.69314718056, " 6.9315E-01"},
                  { 1E-100, " 1.0000-100"} };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      disco::Scientific< 11, 4 >::write( pair.first, it );
      disco::Scientific< 11, 4 >::write( 10.0, it );
      REQUIRE( buffer == ( pair.second + " 1.0000E+01" ) );
    }
  }
  std::string buffer("");
  auto it = std::back_inserter(buffer);
  disco::Scientific< 11, 4 >::write( it );
  REQUIRE(buffer == "           ");
}
