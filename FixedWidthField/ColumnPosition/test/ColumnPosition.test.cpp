#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int testNumber = 0;

int main( int argc, const char* argv[] ){
  LOG(INFO) << "";
  LOG(INFO) << "ColumnPosition Tests";
  LOG(INFO) << "=================================";
  int result = Catch::Session().run( argc, argv );
  LOG(INFO) << "ColumnPosition Tests Complete!";
  return result;
}
