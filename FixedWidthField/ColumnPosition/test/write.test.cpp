#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("ColumnPosition write", "[ColumnPosition], [write]"){
  {
    std::string s = "";
    auto it = std::back_inserter( s );
    disco::ColumnPosition< 1 >::write( it );
    REQUIRE( s == " " );
  }
  {
    std::string s = "";
    auto it = std::back_inserter( s );
    disco::ColumnPosition< 2 >::write( it );
    REQUIRE( s == "  " );
  }
}
