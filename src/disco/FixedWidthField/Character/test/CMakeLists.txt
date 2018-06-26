
add_executable( disco.FixedWidthField.Character.test
                Character.test.cpp
                read.test.cpp
                write.test.cpp )
target_compile_options( disco.FixedWidthField.Character.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${disco_appended_flags} )
target_link_libraries( disco.FixedWidthField.Character.test PUBLIC disco ) 
add_test( NAME disco.FixedWidthField.Character COMMAND disco.FixedWidthField.Character.test )