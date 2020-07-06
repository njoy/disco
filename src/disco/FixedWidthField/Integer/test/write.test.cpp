#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Integer write", "[Integer], [write]"){
  {
    std::vector< std::pair< int, std::string > >
      testSet = { 
        { 0, "          0" },
        { 10, "         10" },
        { std::numeric_limits<int>::max(), " 2147483647"},
        { std::numeric_limits<int>::min() + 1, "-2147483647"},
        { +1.00000010e+9, " 1000000100" },
        { +1.00000010e+8, "  100000010" },
        { -1.00000010e+8, " -100000010" },
        { -1.00000010e+9, "-1000000100" },
      };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      njoy::disco::Integer< 11 >::write( pair.first, it );
      std::cout << std::numeric_limits<int>::min() + 1 << std::endl;
      CHECK(buffer == pair.second);
    }

    std::string buffer("");
    auto it = std::back_inserter(buffer);
    std::uint64_t ul = 1;
    njoy::disco::Integer< 11 >::write( ul, it );
    CHECK(buffer == "          1");
  }
  {
    std::vector< std::pair< int, std::string > >
      testSet = { { 0, "       0000" },
                  { 10, "       0010" } };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      njoy::disco::Integer< 11, 4 >::write( pair.first, it );
      CHECK(buffer == pair.second);
    }
    std::string buffer("");
    auto it = std::back_inserter(buffer);
    njoy::disco::Integer< 8 >::write( std::numeric_limits<int>::max(), it );
    CHECK(buffer == "********");
    buffer = "";
    it = std::back_inserter(buffer);
    njoy::disco::Integer< 11, 4 >::write( std::numeric_limits<int>::max(), it );
    CHECK(buffer == " 2147483647");
  }

  std::string buffer("");
  auto it = std::back_inserter(buffer);
  njoy::disco::Integer< 11 >::write( it );
  CHECK(buffer == "           ");
}
