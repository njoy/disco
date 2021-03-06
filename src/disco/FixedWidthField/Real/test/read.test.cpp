#include <string>
#include <unordered_map>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO("Real read", "[Real], [read]"){
  GIVEN("A collection of strings and corresponding double values"){
    std::vector< std::pair< double, std::string > >
      testset{ {    123., {"      +123"} },
               {    123., {"     123.0"} },
               { 123.123, {"   123.123"} },
               {    -123, {"      -123"} },
               {    1E99, {"      1E99"} },
               {   1.E99, {"    1.E+99"} },
               {  1.E-99, {"     1E-99"} },
               {  1.E-99, {"    1.0-99"} },
               {    123., {"+123      "} },
               {    123., {"123.0     "} },
               { 123.123, {"123.123   "} },
               {    -123, {"-123      "} },
               {    1E99, {"1E99      "} },
               {   1.E99, {"1.E+99    "} },
               {  1.E-99, {"1E-99     "} },
               {  1.E-99, {"1.0-99    "} },
               {    123., {"  +123    "} },
               {    123., {"  123.0   "} },
               { 123.123, {" 123.123  "} },
               {    -123, {"  -123    "} },
               {    1E99, {"    1E99  "} },
               {   1.E99, {"  1.E+99  "} },
               {  1.E-99, {"   1E-99  "} },
               {  1.E-99, {"  1.0-99  "} } };

    THEN("the string will parse to the corresponding value"){
      for ( const auto& pair : testset ){
        const auto& reference = std::get<0>(pair);
        const auto& string = std::get<1>(pair);

        auto begin = string.begin();
        auto end = string.end();
        auto result = njoy::disco::Real<10>::read<double>(begin, end);
        auto error = std::abs( ( result - reference ) / reference );
        REQUIRE( error < 1E-15 );
        REQUIRE( end - begin == 0 );
      }
    }
  }

  GIVEN("A collection of strings and corresponding double values with 11 digits"){
    std::vector< std::pair< double, std::string > >
      testset{ {    123., {"       +123"} },
               {    123., {"      123.0"} },
               { 123.123, {"    123.123"} },
               {    -123, {"       -123"} },
               {    1E99, {"       1E99"} },
               {   1.E99, {"     1.E+99"} },
               {  1.E-99, {"      1E-99"} },
               {  1.E-99, {"     1.0-99"} },
               {    100., {"10.000000+1"} },
               {    100., {" 1.000000+2"} },
               {    123., {"+123       "} },
               {    123., {"123.0      "} },
               { 123.123, {"123.123    "} },
               {    -123, {"-123       "} },
               {    1E99, {"1E99       "} },
               {   1.E99, {"1.E+99     "} },
               {  1.E-99, {"1E-99      "} },
               {  1.E-99, {"1.0-99     "} },
               {    123., {"  +123     "} },
               {    123., {"  123.0    "} },
               { 123.123, {" 123.123   "} },
               {    -123, {"  -123     "} },
               {    1E99, {"    1E99   "} },
               {   1.E99, {"  1.E+99   "} },
               {  1.E-99, {"   1E-99   "} },
               {  1.E-99, {"  1.0-99   "} } };

    THEN("the string will parse to the corresponding value"){
      for ( const auto& pair : testset ){
        const auto& reference = std::get<0>(pair);
        const auto& string = std::get<1>(pair);

        auto begin = string.begin();
        auto end = string.end();
        auto result = njoy::disco::Real<11>::read<double>(begin, end);
        auto error = std::abs( ( result - reference ) / reference );
        REQUIRE( error < 1E-15 );
        REQUIRE( end - begin == 0 );
      }
    }
  }

  GIVEN("a blank string"){
    std::string blank {"          "};
    THEN("the string will be parsed to zero"){
      auto begin = blank.begin();
      auto end = blank.end();
      auto result = njoy::disco::Real<10>::read<double>(begin, end);
      REQUIRE( result == 0 );
      REQUIRE( end - begin == 0 );
    }
  }

  GIVEN("a strings truncated with newline or EOF characters"){
    std::string ten = "   10  ";

    std::vector<std::string> truncatedStrings
    { {ten + '\n'},
      {ten + char{std::char_traits<char>::eof()}} };

    THEN("parsing will terminate at the last character"){
      for( const auto& string : truncatedStrings ){
        auto begin = string.begin();
        auto end = string.end();
        auto result = njoy::disco::Real<10>::read<double>(begin, end);
        REQUIRE( result == 10.0 );
        REQUIRE( *begin == string.back() );
        REQUIRE( end - begin  == 1 );
      }
    }
  }

  std::vector< std::string >
    zero = {  "         0", "       0E0", "      0E+0", "      0E-0",
              "       0e0", "      0e+0", "      0e-0", "       0D0",
              "      0D+0", "      0D-0", "       0d0", "      0d+0",
              "      0d-0", "       0+0", "       0-0", "        0.",
              "      0.E0", "     0.E+0", "     0.E-0", "      0.e0",
              "     0.e+0", "     0.e-0", "      0.D0", "     0.D+0",
              "     0.D-0", "      0.d0", "     0.d+0", "     0.d-0",
              "      0.+0", "      0.-0", "       0.0", "     0.0E0",
              "    0.0E+0", "    0.0E-0", "     0.0e0", "    0.0e+0",
              "    0.0e-0", "     0.0D0", "    0.0D+0", "    0.0D-0",
              "     0.0d0", "    0.0d+0", "    0.0d-0", "     0.0+0",
              "     0.0-0", "        +0", "      +0E0", "     +0E+0",
              "     +0E-0", "      +0e0", "     +0e+0", "     +0e-0",
              "      +0D0", "     +0D+0", "     +0D-0", "      +0d0",
              "     +0d+0", "     +0d-0", "      +0+0", "      +0-0",
              "       +0.", "     +0.E0", "    +0.E+0", "    +0.E-0",
              "     +0.e0", "    +0.e+0", "    +0.e-0", "     +0.D0",
              "    +0.D+0", "    +0.D-0", "     +0.d0", "    +0.d+0",
              "    +0.d-0", "     +0.+0", "     +0.-0", "      +0.0",
              "    +0.0E0", "   +0.0E+0", "   +0.0E-0", "    +0.0e0",
              "   +0.0e+0", "   +0.0e-0", "    +0.0D0", "   +0.0D+0",
              "   +0.0D-0", "    +0.0d0", "   +0.0d+0", "   +0.0d-0",
              "    +0.0+0", "    +0.0-0", "        -0", "      -0E0",
              "     -0E+0", "     -0E-0", "      -0e0", "     -0e+0",
              "     -0e-0", "      -0D0", "     -0D+0", "     -0D-0",
              "      -0d0", "     -0d+0", "     -0d-0", "      -0+0",
              "      -0-0", "       -0.", "     -0.E0", "    -0.E+0",
              "    -0.E-0", "     -0.e0", "    -0.e+0", "    -0.e-0",
              "     -0.D0", "    -0.D+0", "    -0.D-0", "     -0.d0",
              "    -0.d+0", "    -0.d-0", "     -0.+0", "     -0.-0",
              "      -0.0", "    -0.0E0", "   -0.0E+0", "   -0.0E-0",
              "    -0.0e0", "   -0.0e+0", "   -0.0e-0", "    -0.0D0",
              "   -0.0D+0", "   -0.0D-0", "    -0.0d0", "   -0.0d+0",
              "   -0.0d-0", "    -0.0+0", "    -0.0-0", "       0E1",
              "      0E+1", "       0e1", "      0e+1", "       0D1",
              "      0D+1", "       0d1", "      0d+1", "       0+1",
              "      +0E1", "     +0E+1", "      +0e1", "     +0e+1",
              "      +0D1", "     +0D+1", "      +0d1", "     +0d+1",
              "      +0+1", "      0E-1", "      0e-1", "      0D-1",
              "      0d-1", "       0-1", "     +0E-1", "     +0e-1",
              "     +0D-1", "     +0d-1", "      +0-1", "      -0E1",
              "     -0E+1", "      -0e1", "     -0e+1", "      -0D1",
              "     -0D+1", "      -0d1", "     -0d+1", "      -0+1",
              "     -0E-1", "     -0e-1", "     -0D-1", "     -0d-1",
              "      -0-1", "          " };

  for ( auto& test_string : zero ){
    auto begin = test_string.begin();
    auto end = test_string.end();
    auto result = njoy::disco::Real<10>::read<double>(begin, end);
    REQUIRE( result == 0 );
    REQUIRE( end - begin == 0 );
  }

  const std::unordered_map
             < double, std::vector<std::string> > valid =
    {{    -0.5, { "       -.5", "     -.5E0", "    -.5E+0", "    -.5E-0",
                  "     -.5e0", "    -.5e+0", "    -.5e-0", "     -.5D0",
                  "    -.5D+0", "    -.5D-0", "     -.5d0", "    -.5d+0",
                  "    -.5d-0", "     -.5+0", "     -.5-0", "      -0.5",
                  "    -0.5E0", "   -0.5E+0", "   -0.5E-0", "    -0.5e0",
                  "   -0.5e+0", "   -0.5e-0", "    -0.5D0", "   -0.5D+0",
                  "   -0.5D-0", "    -0.5d0", "   -0.5d+0", "   -0.5d-0",
                  "     -0.50", "    -0.5-0", "     -0.50", "   -0.50E0",
                  "  -0.50E+0", "  -0.50E-0", "   -0.50e0", "  -0.50e+0",
                  "  -0.50e-0", "   -0.50D0", "  -0.50D+0", "  -0.50D-0",
                  "   -0.50d0", "  -0.50d+0", "  -0.50d-0", "   -0.50+0",
                  "   -0.50-0", "      -.50", "    -.50E0", "   -.50E+0",
                  "   -.50E-0", "    -.50e0", "   -.50e+0", "   -.50e-0",
                  "    -.50D0", "   -.50D+0", "   -.50D-0", "    -.50d0",
                  "   -.50d+0", "   -.50d-0", "    -.50+0", "    -.50-0",
                  "   -0.05E1", "  -0.05E+1", "   -0.05e1", "  -0.05e+1",
                  "   -0.05D1", "  -0.05D+1", "   -0.05d1", "  -0.05d+1",
                  "   -0.05+1", "     -5E-1", "     -5e-1", "     -5D-1",
                  "     -5d-1", "      -5-1"}},
     {     0.5, { "        .5", "      .5E0", "     .5E+0", "     .5E-0",
                  "      .5e0", "     .5e+0", "     .5e-0", "      .5D0",
                  "     .5D+0", "     .5D-0", "      .5d0", "     .5d+0",
                  "     .5d-0", "      .5+0", "      .5-0", "       0.5",
                  "     0.5E0", "    0.5E+0", "    0.5E-0", "     0.5e0",
                  "    0.5e+0", "    0.5e-0", "     0.5D0", "    0.5D+0",
                  "    0.5D-0", "     0.5d0", "    0.5d+0", "    0.5d-0",
                  "      0.50", "     0.5-0", "      0.50", "    0.50E0",
                  "   0.50E+0", "   0.50E-0", "    0.50e0", "   0.50e+0",
                  "   0.50e-0", "    0.50D0", "   0.50D+0", "   0.50D-0",
                  "    0.50d0", "   0.50d+0", "   0.50d-0", "    0.50+0",
                  "    0.50-0", "       .50", "     .50E0", "    .50E+0",
                  "    .50E-0", "     .50e0", "    .50e+0", "    .50e-0",
                  "     .50D0", "    .50D+0", "    .50D-0", "     .50d0",
                  "    .50d+0", "    .50d-0", "     .50+0", "     .50-0",
                  "       +.5", "     +.5E0", "    +.5E+0", "    +.5E-0",
                  "     +.5e0", "    +.5e+0", "    +.5e-0", "     +.5D0",
                  "    +.5D+0", "    +.5D-0", "     +.5d0", "    +.5d+0",
                  "    +.5d-0", "     +.5+0", "     +.5-0", "      +0.5",
                  "    +0.5E0", "   +0.5E+0", "   +0.5E-0", "    +0.5e0",
                  "   +0.5e+0", "   +0.5e-0", "    +0.5D0", "   +0.5D+0",
                  "   +0.5D-0", "    +0.5d0", "   +0.5d+0", "   +0.5d-0",
                  "     +0.50", "    +0.5-0", "     +0.50", "   +0.50E0",
                  "  +0.50E+0", "  +0.50E-0", "   +0.50e0", "  +0.50e+0",
                  "  +0.50e-0", "   +0.50D0", "  +0.50D+0", "  +0.50D-0",
                  "   +0.50d0", "  +0.50d+0", "  +0.50d-0", "   +0.50+0",
                  "   +0.50-0", "      +.50", "    +.50E0", "   +.50E+0",
                  "   +.50E-0", "    +.50e0", "   +.50e+0", "   +.50e-0",
                  "    +.50D0", "   +.50D+0", "   +.50D-0", "    +.50d0",
                  "   +.50d+0", "   +.50d-0", "    +.50+0", "    +.50-0",
                  "    0.05E1", "   0.05E+1", "    0.05e1", "   0.05e+1",
                  "    0.05D1", "   0.05D+1", "    0.05d1", "   0.05d+1",
                  "    0.05+1", "   +0.05E1", "  +0.05E+1", "   +0.05e1",
                  "  +0.05e+1", "   +0.05D1", "  +0.05D+1", "   +0.05d1",
                  "  +0.05d+1", "   +0.05+1", "      5E-1", "      5e-1",
                  "      5D-1", "      5d-1", "       5-1", "     +5E-1",
                  "     +5e-1", "     +5D-1", "     +5d-1", "      +5-1" }},
     {   -10.0, { "       -10", "     -10E0", "    -10E+0", "    -10E-0",
                  "     -10e0", "    -10e+0", "    -10e-0", "     -10D0",
                  "    -10D+0", "    -10D-0", "     -10d0", "    -10d+0",
                  "    -10d-0", "     -10+0", "     -10-0", "      -10.",
                  "    -10.E0", "   -10.E+0", "   -10.E-0", "    -10.e0",
                  "   -10.e+0", "   -10.e-0", "    -10.D0", "   -10.D+0",
                  "   -10.D-0", "    -10.d0", "   -10.d+0", "   -10.d-0",
                  "    -10.+0", "    -10.-0", "     -10.0", "   -10.0E0",
                  "  -10.0E+0", "  -10.0E-0", "   -10.0e0", "  -10.0e+0",
                  "  -10.0e-0", "   -10.0D0", "  -10.0D+0", "  -10.0D-0",
                  "   -10.0d0", "  -10.0d+0", "  -10.0d-0", "   -10.0+0",
                  "   -10.0-0", "      -1E1", "     -1E+1", "      -1e1",
                  "     -1e+1", "      -1D1", "     -1D+1", "      -1d1",
                  "     -1d+1", "      -1+1", "   -100E-1", "   -100e-1",
                  "   -100D-1", "   -100d-1", "    -100-1"}},
     {    10.0, { "        10", "      10E0", "     10E+0", "     10E-0",
                  "      10e0", "     10e+0", "     10e-0", "      10D0",
                  "     10D+0", "     10D-0", "      10d0", "     10d+0",
                  "     10d-0", "      10+0", "      10-0", "       10.",
                  "     10.E0", "    10.E+0", "    10.E-0", "     10.e0",
                  "    10.e+0", "    10.e-0", "     10.D0", "    10.D+0",
                  "    10.D-0", "     10.d0", "    10.d+0", "    10.d-0",
                  "     10.+0", "     10.-0", "      10.0", "    10.0E0",
                  "   10.0E+0", "   10.0E-0", "    10.0e0", "   10.0e+0",
                  "   10.0e-0", "    10.0D0", "   10.0D+0", "   10.0D-0",
                  "    10.0d0", "   10.0d+0", "   10.0d-0", "    10.0+0",
                  "    10.0-0", "       +10", "     +10E0", "    +10E+0",
                  "    +10E-0", "     +10e0", "    +10e+0", "    +10e-0",
                  "     +10D0", "    +10D+0", "    +10D-0", "     +10d0",
                  "    +10d+0", "    +10d-0", "     +10+0", "     +10-0",
                  "      +10.", "    +10.E0", "   +10.E+0", "   +10.E-0",
                  "    +10.e0", "   +10.e+0", "   +10.e-0", "    +10.D0",
                  "   +10.D+0", "   +10.D-0", "    +10.d0", "   +10.d+0",
                  "   +10.d-0", "    +10.+0", "    +10.-0", "     +10.0",
                  "   +10.0E0", "  +10.0E+0", "  +10.0E-0", "   +10.0e0",
                  "  +10.0e+0", "  +10.0e-0", "   +10.0D0", "  +10.0D+0",
                  "  +10.0D-0", "   +10.0d0", "  +10.0d+0", "  +10.0d-0",
                  "   +10.0+0", "   +10.0-0", "       1E1", "      1E+1",
                  "       1e1", "      1e+1", "       1D1", "      1D+1",
                  "       1d1", "      1d+1", "       1+1", "      +1E1",
                  "     +1E+1", "      +1e1", "     +1e+1", "      +1D1",
                  "     +1D+1", "      +1d1", "     +1d+1", "      +1+1",
                  "    100E-1", "    100e-1", "    100D-1", "    100d-1",
                  "     100-1", "   +100E-1", "   +100e-1", "   +100D-1",
                  "   +100d-1", "    +100-1"}},
     { 3.14159, { "   3.14159", "3.14159   ", " 3.14159E0", "3.14159E0 ",
                  "3.14159E+0", "3.14159E-0", "3.14159e+0", "3.14159e0 ",
                  "3.14159e-0", " 3.14159D0", "3.14159D0 ", "3.14159D+0",
                  "3.14159D-0", " 3.14159d0", "3.14159d0 ", "3.14159d+0",
                  "3.14159d-0", " 3.14159+0", "3.14159+0 ", " 3.14159-0",
                  "3.14159-0 ", " .314159E1", ".314159E1 " , ".314159E+1",
                  " .314159e1", ".314159e1 ", ".314159e+1", " .314159D1",
                  ".314159D1 ", ".314159D+1", " .314159d1", ".314159d1 ",
                  ".314159d+1", " .314159+1", ".314159+1 ", "0.314159E1",
                  "0.314159E1", "0.314159e1", ".314159e+1", "0.314159D1",
                  ".314159D+1", "0.314159d1", ".314159d+1", "0.314159+1",
                  "31.4159E-1", "31.4159e-1", "31.4159D-1", "31.4159d-1",
                  " 31.4159-1", "31.4159-1 ", "  +3.14159", "+3.14159  ",
                  "+3.14159E0", "+3.14159D0", "+3.14159e0", "+3.14159d0" }}};

  for ( auto& number : valid ){
    for ( auto& string : number.second ){
      auto begin = string.begin();
      auto end = string.end();
      auto result = njoy::disco::Real<10>::read<double>(begin, end);
      auto error = std::abs( ( result - number.first ) / number.first );
      REQUIRE( error < 1E-15 );
      REQUIRE( end - begin == 0 );
    }
  }

  std::vector< std::string >
    infinityStrings = { "  infinity", "  Infinity",
                        " +infinity", " +Infinity",
                        "       inf", "       Inf",
                        "      +inf", "      +Inf",
                        "infinity  ", "Infinity  ",
                        "+infinity ", "+Infinity ",
                        "inf       ", "Inf       ",
                        "+inf      ", "+Inf      " };

  for ( auto& string : infinityStrings ){
    auto begin = string.begin();
    auto end = string.end();
    auto result = njoy::disco::Real<10>::read<double>(begin, end);
    REQUIRE( result == std::numeric_limits<double>::infinity() );
    REQUIRE( end - begin == 0 );
  }

  infinityStrings = { " -infinity", " -Infinity",
                      " -infinity", " -Infinity",
                      "      -inf", "      -Inf",
                      "      -inf", "      -Inf",
                      "-infinity ", "-Infinity ",
                      "-infinity ", "-Infinity ",
                      "-inf      ", "-Inf      ",
                      "-inf      ", "-Inf      " };
  for ( auto& string : infinityStrings ){
    auto begin = string.begin();
    auto end = string.end();
    auto result = njoy::disco::Real<10>::read<double>(begin, end);
    REQUIRE( result == -std::numeric_limits<double>::infinity() );
    REQUIRE( end - begin == 0 );
  }

  GIVEN("A collection of invalid strings"){
    std::vector< std::string >
      testset{{"         +"},
              {"       + 1"},
              {"   .      "},
              {"   .inf   "},
              {"        E3"},
              {"    .E3   "},
              {"         E"},
              {"      1.2E"},
              {" -123.0a  "},
              {" -123.0 a "}};

    for ( auto& string : testset ){
      std::cout << string << std::endl;
      auto begin = string.begin();
      auto end = string.end();
      REQUIRE_THROWS( njoy::disco::Real<10>::read<double>(begin, end) );
    }
  }
}
