
add_executable( disco.FixedWidthField.ColumnPosition.test
                write.test.cpp
                ColumnPosition.test.cpp
                read.test.cpp )
target_compile_options( disco.FixedWidthField.ColumnPosition.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${disco_appended_flags} )
target_link_libraries( disco.FixedWidthField.ColumnPosition.test PUBLIC disco ) 
add_test( NAME disco.FixedWidthField.ColumnPosition COMMAND disco.FixedWidthField.ColumnPosition.test )