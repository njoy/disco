#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "disco.hpp"

INITIALIZE_EASYLOGGINGPP

int testNumber = 0;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "Real Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "Real Tests Complete!";
  return result;
}
