add_executable( ColumnPosition.test
                ColumnPosition.test.cpp
                read.test.cpp
                write.test.cpp )
set( test_flags ${disco_compiler_flags} )
separate_arguments( test_flags_list UNIX_COMMAND "${test_flags}" )
foreach( flag IN LISTS test_flags_list )
    target_compile_options( ColumnPosition.test PUBLIC ${flag} )
endforeach( flag )
set_target_properties( ColumnPosition.test PROPERTIES LINK_FLAGS "${test_flags}" )
target_link_libraries( ColumnPosition.test PUBLIC disco )
add_test( NAME ColumnPosition COMMAND ColumnPosition.test ) 
