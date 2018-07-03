
add_executable( disco.Record.test
                read.test.cpp
                Record.test.cpp
                write.test.cpp )
target_compile_options( disco.Record.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${disco_appended_flags} )
target_link_libraries( disco.Record.test PUBLIC disco ) 
add_test( NAME disco.Record COMMAND disco.Record.test )