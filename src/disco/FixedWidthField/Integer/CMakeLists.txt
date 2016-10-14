if(${verbose_traversal})
  message(STATUS "Entered Integer directory")
endif(${verbose_traversal})

set(long_path "${disco_HEADER_DIR}/FixedWidthField/Integer")

set(header_only_subdirs "")
list(APPEND header_only_subdirs)

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
  "src/read"
  "src/write"
  "src/parseInteger"
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
  list(APPEND testLabels Integer)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting Integer directory")
endif(${verbose_traversal})
