#include <string>
#include <unordered_map>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

using namespace njoy::disco;

SCENARIO("Record read", "[Record], [read]"){
  {
    double sink;
    std::string source("       11.0\n");
    auto it = source.begin();
    auto end = source.end();
    
    Record< Scientific< 11, 4 > >::read( it, end, sink );
    REQUIRE( sink == 11.0 );
  }
  {
    std::string source = "        1.0        2.0        3.0        4.0\n";
    auto  it = source.begin();
    auto  end = source.end();
    double sink1;
    double sink2;
    double sink3;
    double sink4;
    Record< Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 > >::read( it, end, sink1, sink2, sink3, sink4 );
    REQUIRE( sink1 == 1.0 );
    REQUIRE( sink2 == 2.0 );
    REQUIRE( sink3 == 3.0 );
    REQUIRE( sink4 == 4.0 );
    std::string sink("");
    auto sinkit = std::back_inserter( sink );
    Record< Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 > >::write( sinkit, sink1, sink2, sink3, sink4 );
    REQUIRE( sink == " 1.0000E+00 2.0000E+00 3.0000E+00 4.0000E+00\n" );
  }
    {
    std::string source = "        1.0        2.0        3.0        4.0       1234  foobar\n";
    auto  it = source.begin();
    auto  end = source.end();
    double sink1;
    double sink2;
    double sink3;
    double sink4;
    int sink5;
    std::string sink6;
    Record< Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Integer< 11 >,
            Character< 11 > >::read( it, end, sink1, sink2, sink3, sink4, sink5, sink6 );
    REQUIRE( sink1 == 1.0 );
    REQUIRE( sink2 == 2.0 );
    REQUIRE( sink3 == 3.0 );
    REQUIRE( sink4 == 4.0 );
    REQUIRE( sink5 == 1234 );
    REQUIRE( sink6 == "  foobar   " );
  }
  {
    std::vector< double > sink(4, 0.0);
    auto it = sink.begin(); // can't use back inserter =(
    std::string source = "        1.0        2.0        3.0        4.0\n";
    auto sourceIt = source.begin();
    auto end = source.end();
    Record< Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 > >::read( sourceIt, end, it[0], it[1], it[2], it[3] );
    REQUIRE( sink[0] == 1 );
    REQUIRE( sink[1] == 2 );
    REQUIRE( sink[2] == 3 );
    REQUIRE( sink[3] == 4 );
  }
  {
    std::vector< double > sink(4, 0.0);
    auto it = sink.begin();
    std::string source = "        1.0        2.0        3.0        4.0\n";
    auto sourceIt = source.begin();
    auto end = source.end();
    Record< Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 > >::read( sourceIt, end, it[0], it[1], it[2] );
    REQUIRE( sink[0] == 1 );
    REQUIRE( sink[1] == 2 );
    REQUIRE( sink[2] == 3 );
    REQUIRE( sink[3] == 0 );
  }
}
