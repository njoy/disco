add_executable( Integer.test
                Integer.test.cpp
                read.test.cpp
                write.test.cpp )
set( test_flags ${disco_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( Integer.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( Integer.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( Integer.test PUBLIC disco )
add_test( NAME Integer COMMAND Integer.test ) 
