if(${verbose_traversal})
  message(STATUS "Entered Record directory")
endif(${verbose_traversal})

if(${local_testing})
  list(APPEND testLabels Record)
  add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/test" )
endif(${local_testing})

if(${verbose_traversal})
  message(STATUS "Exiting Record directory")
endif(${verbose_traversal})
