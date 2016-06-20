if(${verbose_traversal})
  message(STATUS "Entered Real directory")
endif(${verbose_traversal})

set(long_path "${disco_HEADER_DIR}/FixedWidthField/Real")

set(header_only_subdirs "")
list(APPEND header_only_subdirs
  "Scientific"
  )

set(subdirs "")
list(APPEND subdirs
  ${header_only_subdirs}
  )
  
foreach (subdir ${header_only_subdirs})
  if(NOT(EXISTS "${long_path}/${subdir}"))
    file(MAKE_DIRECTORY "${long_path}/${subdir}")
  endif(NOT(EXISTS "${long_path}/${subdir}"))
endforeach (subdir)

if(NOT(EXISTS "${long_path}/src"))
  file(MAKE_DIRECTORY "${long_path}/src")
endif(NOT(EXISTS "${long_path}/src"))

set(headers "")
list(APPEND headers
  "src/noDigits"
  "src/parseSign"
  "src/parseBase"
  "src/parseFraction"
  "src/parseExponent"
  "src/parseInfinity"
  "src/read"
  "Pow"
  "Exponentiation"
  ${subdirs}
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in"
    "${long_path}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

foreach (subdir ${subdirs})
  add_subdirectory( ${subdir} )
endforeach (subdir)

if(${local_testing})
  list(APPEND testLabels Real)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting Real directory")
endif(${verbose_traversal})
