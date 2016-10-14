add_executable( Real.test
                parseBase.test.cpp
                parseExponent.test.cpp
                parseFraction.test.cpp
                parseSign.test.cpp
                read.test.cpp
                Real.test.cpp )
set( test_flags ${disco_compiler_flags} )
separate_arguments( test_flags )
foreach( flag IN LISTS test_flags )
    target_compile_options( Real.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( Real.test PROPERTIES LINK_FLAGS "${disco_compiler_flags}" )
target_link_libraries( Real.test PUBLIC disco )
add_test( NAME Real COMMAND Real.test ) 
