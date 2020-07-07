#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("FixedPoint write", "[FixedPoint], [write]"){
  {
    constexpr double infinity = std::numeric_limits<double>::infinity();

    std::vector< std::pair< double, std::string > >
      testSet = { 
        { 0.0,             " 0.000000+0" },  
        { 10.0,            " 1.000000+1" },
        { 3.14159,         " 3.141590+0"},   
        { infinity,        "   Infinity"},   
        { 0.69314718056,   " 0.69314718"},   
        { 1E-100,          "***********" },  
        { 1E10,            " 1.00000+10" },  
        { 1E-10,           " 1.00000-10" },  
        { -1E10,           "-1.00000+10" },  
        { -1E-10,          "-1.00000-10" },  
        { -10.0,           "-1.000000+1" },  
        { -3.14159,        "-3.141590+0"},   
        { -infinity,       "  -Infinity"},   
        { -0.69314718056,  "-0.69314718"},   

        // Test scientific notation
        { +1.e+10, " 1.00000+10" },
        { +1.0e+9, " 1.000000+9" },
        { +1.0e+8, " 1.000000+8" },
        { +1.0e+7, " 1.000000+7" },
        { +1.0e+6, " 1.000000+6" },
        { +1.0e+5, " 1.000000+5" },
        { +1.0e+4, " 1.000000+4" },
        { +1.0e+3, " 1.000000+3" },
        { +1.0e+2, " 1.000000+2" },
        { +1.0e+1, " 1.000000+1" },
        { +1.0000, " 1.000000+0" },
        { +0.1000, " 1.000000-1" },
        { +0.0100, " 1.000000-2" },
        { +0.0010, " 1.000000-3" },
        { +0.0001, " 1.000000-4" },
        { 0.00000, " 0.000000+0" },
        { -0.0001, "-1.000000-4" },
        { -0.0010, "-1.000000-3" },
        { -0.0100, "-1.000000-2" },
        { -0.1000, "-1.000000-1" },
        { -1.0000, "-1.000000+0" },
        { -1.0e+1, "-1.000000+1" },
        { -1.0e+2, "-1.000000+2" },
        { -1.0e+3, "-1.000000+3" },
        { -1.0e+4, "-1.000000+4" },
        { -1.0e+5, "-1.000000+5" },
        { -1.0e+6, "-1.000000+6" },
        { -1.0e+7, "-1.000000+7" },
        { -1.0e+8, "-1.000000+8" },
        { -1.0e+9, "-1.000000+9" },
        { -1.0e+10, "-1.00000+10" },

        // Test fixed notation
        { +1.0000001e+10, " 1.00000+10" },
        { +1.00000010e+9, " 1000000100" },
        { +1.00000010e+8, "  100000010" },
        { +1.00000010e+7, " 10000001.0" },
        { +1.00000010e+6, " 1000000.10" },
        { +1.00000010e+5, " 100000.010" },
        { +1.00000010e+4, " 10000.0010" },
        { +1.00000010e+3, " 1000.00010" },
        { +1.00000010e+2, " 100.000010" },
        { +1.00000010e+1, " 10.0000010" },
        { +1.00000010000, " 1.00000010" },
        { +0.10000001000, " 0.10000001" },
        { +0.01000000100, " 1.000000-2" },
        { +0.00100000010, " 1.000000-3" },
        { +0.00010000001, " 1.000000-4" },
        { 0.000000000000, " 0.000000+0" },
        { -0.00010000001, "-1.000000-4" },
        { -0.00100000010, "-1.000000-3" },
        { -0.01000000100, "-1.000000-2" },
        { -0.10000001000, "-0.10000001" },
        { -1.00000010000, "-1.00000010" },
        { -1.00000010e+1, "-10.0000010" },
        { -1.00000010e+2, "-100.000010" },
        { -1.00000010e+3, "-1000.00010" },
        { -1.00000010e+4, "-10000.0010" },
        { -1.00000010e+5, "-100000.010" },
        { -1.00000010e+6, "-1000000.10" },
        { -1.00000010e+7, "-10000001.0" },
        { -1.00000010e+8, " -100000010" },
        { -1.00000010e+9, "-1000000100" },
        { -1.0000001e+10, "-1.00000+10" },

        { +1.000000004, " 1.000000+0" },
        { -1.000000004, "-1.000000+0" },

        { +1.000000009, " 1.00000001" },
        { -1.000000009, "-1.00000001" },

        { +1.000000099, " 1.00000010" },
        { -1.000000099, "-1.00000010" },

        { +1.000000999, " 1.000001+0" },
        { -1.000000999, "-1.000001+0" },
      };

    for ( auto& pair : testSet ){
      THEN( "we can test '" + pair.second + "'" ){
        std::string buffer("");
        auto it = std::back_inserter(buffer);
        njoy::disco::ENDF::write( pair.first, it );
        CHECK( buffer == pair.second );
      } // THEN
    }
  }
}
