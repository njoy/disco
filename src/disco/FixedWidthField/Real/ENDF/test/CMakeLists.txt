add_executable( ENDF.test
                ENDF.test.cpp
                write.test.cpp )
set( test_flags ${disco_compiler_flags} )
separate_arguments( test_flags )
foreach( flag IN LISTS test_flags )
    target_compile_options( ENDF.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( ENDF.test PROPERTIES LINK_FLAGS "${disco_compiler_flags}" )
target_link_libraries( ENDF.test PUBLIC disco )
add_test( NAME ENDF COMMAND ENDF.test ) 
