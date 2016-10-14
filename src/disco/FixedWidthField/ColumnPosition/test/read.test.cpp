#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("ColumnPosition read", "[ColumnPosition], [read]"){
  {
    std::string s = " ";
    auto begin = s.begin();
    auto it = begin;
    auto end = s.end();
    disco::ColumnPosition< 1 >::read( it, end );
    REQUIRE( ( it - begin ) == 1u );
  }
  {
    std::string s = "  ";
    auto begin = s.begin();
    auto it = begin;
    auto end = s.end();
    disco::ColumnPosition< 2 >::read( it, end );
    REQUIRE( ( it - begin ) == 2u );
  }
  {
    std::string s = "     ";
    auto begin = s.begin();
    auto it = begin;
    auto end = s.end();
    disco::ColumnPosition< 2 >::read( it, end );
    REQUIRE( ( it - begin ) == 2u );
  }
  {
    std::string s = "x";
    auto begin = s.begin();
    auto it = begin;
    auto end = s.end();
    disco::ColumnPosition< 1 >::read( it, end );
    REQUIRE( ( it - begin ) == 1u );
  }
  {
    std::string s = "   \n  ";
    auto begin = s.begin();
    auto it = begin;
    auto end = s.end();
    disco::ColumnPosition< 6 >::read( it, end );
    REQUIRE( ( it - begin ) == 3u );
  }
}
