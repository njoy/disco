add_executable( Character.test
                Character.test.cpp
                read.test.cpp
                write.test.cpp )
set( test_flags ${disco_compiler_flags} )
separate_arguments( test_flags )
foreach( flag IN LISTS test_flags )
    target_compile_options( Character.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( Character.test PROPERTIES LINK_FLAGS "${disco_compiler_flags}" )
target_link_libraries( Character.test PUBLIC disco )
add_test( NAME Character COMMAND Character.test ) 
