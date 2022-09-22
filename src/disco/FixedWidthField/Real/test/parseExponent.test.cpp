#include <string>
#include <vector>

#include "disco.hpp"
#include "catch.hpp"

SCENARIO( "Real parse exponent" ) {

  std::string test;
  auto iter = test.begin();
  uint16_t position;

  test = "+123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "+ 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "E+123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "E+ 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "E123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "E 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "e+123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "e+ 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "e123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "e 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "D+123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "D+ 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "D123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "D 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "d+123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "d+ 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "d123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "d 123";
  iter = test.begin();
  position = 0;
  CHECK( +123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "-123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "- 123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "E-123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "E- 123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "e-123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "e- 123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "D-123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "D- 123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "d-123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );

  test = "d- 123";
  iter = test.begin();
  position = 0;
  CHECK( -123 == njoy::disco::Real<6>::parseExponent( iter, position ) );
}
