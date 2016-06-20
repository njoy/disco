#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "disco.hpp"

INITIALIZE_EASYLOGGINGPP

int testNumber = 0;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "Scientific Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "Scientific Tests Complete!";
  return result;
}
