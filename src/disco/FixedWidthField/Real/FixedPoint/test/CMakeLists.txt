add_executable( FixedPoint.test
                FixedPoint.test.cpp
                write.test.cpp )
set( test_flags ${disco_compiler_flags} )
separate_arguments( test_flags )
foreach( flag IN LISTS test_flags )
    target_compile_options( FixedPoint.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( FixedPoint.test PROPERTIES LINK_FLAGS "${disco_compiler_flags}" )
target_link_libraries( FixedPoint.test PUBLIC disco )
add_test( NAME FixedPoint COMMAND FixedPoint.test ) 
