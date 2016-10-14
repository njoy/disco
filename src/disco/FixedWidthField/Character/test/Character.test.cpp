#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int testNumber = 0;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "Character Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "Character Tests Complete!";
  return result;
}
