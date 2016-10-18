#include <string>
#include <unordered_map>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

using namespace njoy::disco;

SCENARIO("Record write", "[Record], [write]"){
  {
    double source = 11.0;
    std::string sink;
    auto it = std::back_inserter( sink );
    Record< Scientific< 11, 4 > >::write( it, source );
    REQUIRE( sink == " 1.1000E+01\n" );
  }
  {
    std::string sink("");
    auto it = std::back_inserter( sink );
    double source1 = 1.0;
    double source2 = 2.0;
    double source3 = 3.0;
    int source4 = 1234;
    Record< Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Scientific< 11, 4 >,
            Integer< 11, 6 > >::write( it, source1, source2, source3, source4 );
    REQUIRE( sink == " 1.0000E+00 2.0000E+00 3.0000E+00     001234\n" );
  }
}
