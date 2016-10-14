#!/bin/bash
if [ "$CC" = "gcc" ]; then export VERSION=-6; fi;
if [ "$CC" = "clang" ]; then export VERSION=-3.8; fi;

if [ "$TRAVIS_OS_NAME" = "linux" ]; then
  sudo update-alternatives --install /usr/bin/$CC $CC /usr/bin/$CC$VERSION 90 --slave /usr/bin/$CXX $CXX /usr/bin/$CC$VERSION
  sudo update-alternatives --config $CC
fi

./fetch_subprojects.py
mkdir build
cd build
cmake -D build_type=$build_type \
      -D static_libraries=$static_libraries \
      -D appended_flags=$appended_flags ..
make -j2
export COMPILATION_FAILURE=$?
ctest --output-on-failure -j2
export TEST_FAILURE=$?
if [ "$build_type" = "coverage" ]
then
    pip install --user cpp-coveralls
    echo "loading coverage information"
    coveralls  --exclude "/usr/include/" --exclude-pattern ".*subprojects.*|.*test\.cpp" --root ".." --build-root "." --gcov-options '\-lp'
fi
if [ $COMPILATION_FAILURE -ne 0 ] || [ $TEST_FAILURE -ne 0 ];
then
    exit 1
else
    exit 0
fi
