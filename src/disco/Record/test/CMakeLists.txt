add_executable( Record.test
                read.test.cpp
                Record.test.cpp
                write.test.cpp )
set( test_flags ${disco_compiler_flags} )
separate_arguments( test_flags )
foreach( flag IN LISTS test_flags )
    target_compile_options( Record.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( Record.test PROPERTIES LINK_FLAGS "${disco_compiler_flags}" )
target_link_libraries( Record.test PUBLIC disco )
add_test( NAME Record COMMAND Record.test ) 
