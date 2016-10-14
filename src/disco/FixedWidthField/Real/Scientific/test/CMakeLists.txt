add_executable( Scientific.test
                Scientific.test.cpp
                write.test.cpp )
set( test_flags ${disco_compiler_flags} )
separate_arguments( test_flags )
foreach( flag IN LISTS test_flags )
    target_compile_options( Scientific.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( Scientific.test PROPERTIES LINK_FLAGS "${disco_compiler_flags}" )
target_link_libraries( Scientific.test PUBLIC disco )
add_test( NAME Scientific COMMAND Scientific.test ) 
