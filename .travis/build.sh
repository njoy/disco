#!/bin/bash

if [ "$TRAVIS_OS_NAME" = "linux" ]; then
  sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 90 --slave /usr/bin/g++ g++ /usr/bin/g++-6
  sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.8 90 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-3.8
  sudo update-alternatives --config gcc
  sudo update-alternatives --config clang
  export PATH=/usr/bin:$PATH
  if [ "$CXX" = "clang++" ]; then
      sudo ln -sf /usr/lib/LLVMgold.so /usr/lib/llvm-3.8/lib/LLVMgold.so
      sudo ln -sf /usr/lib/libLTO.so /usr/lib/llvm-3.8/lib/libLTO.so
    export appended_flags=$appended_flags"-stdlib=libstdc++ -B/usr/lib/gold-ld"
  fi;
fi

./fetch_subprojects.py
mkdir build
cd build
cmake -D build_type=$build_type \
      -D static_libraries=$static_libraries \
      -D appended_flags="$appended_flags" ..
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
