#include <iterator>
#include <string>
#include <tuple>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Integer write", "[Integer], [write]"){
  {
    std::vector< std::pair< int, std::string > >
      testSet = { { 0, "          0" },
                  { 10, "         10" },
                  { std::numeric_limits<int>::max(), " 2147483647"},
                  { std::numeric_limits<int>::min() + 1, "-2147483647"} };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      njoy::disco::Integer< 11 >::write( pair.first, it );
      std::cout << std::numeric_limits<int>::min() + 1 << std::endl;
      REQUIRE(buffer == pair.second);
    }
    std::string buffer("");
    auto it = std::back_inserter(buffer);
    std::uint64_t ul = 1;
    njoy::disco::Integer< 11 >::write( ul, it );
    REQUIRE(buffer == "          1");
  }
  {
    std::vector< std::pair< int, std::string > >
      testSet = { { 0, "       0000" },
                  { 10, "       0010" } };
    for ( auto& pair : testSet ){
      std::string buffer("");
      auto it = std::back_inserter(buffer);
      njoy::disco::Integer< 11, 4 >::write( pair.first, it );
      REQUIRE(buffer == pair.second);
    }
    std::string buffer("");
    auto it = std::back_inserter(buffer);
    njoy::disco::Integer< 8 >::write( std::numeric_limits<int>::max(), it );
    REQUIRE(buffer == "********");
    buffer = "";
    it = std::back_inserter(buffer);
    njoy::disco::Integer< 11, 4 >::write( std::numeric_limits<int>::max(), it );
    REQUIRE(buffer == " 2147483647");
  }
  std::string buffer("");
  auto it = std::back_inserter(buffer);
  njoy::disco::Integer< 11 >::write( it );
  REQUIRE(buffer == "           ");
}
