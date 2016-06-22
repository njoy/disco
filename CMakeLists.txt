cmake_minimum_required( VERSION 3.2 )

set(projectName "disco")
set(projectVersion "0.5.0")

if(NOT DEFINED commonCMakeScripts_path)
  set(commonCMakeScripts_path "${CMAKE_SOURCE_DIR}/commonCMakeScripts")
endif(NOT DEFINED commonCMakeScripts_path)

set_property(GLOBAL PROPERTY ${projectName}_HEADER_ONLY TRUE )

include(subprojects.cmake)
include(${commonCMakeScripts_path}/base.cmake)
include(${commonCMakeScripts_path}/doxygen.cmake)

# create the utility build tree header directory and immediate children if necessary
if(NOT(EXISTS "${disco_HEADER_DIR}/FixedWidthField"))
  file(MAKE_DIRECTORY "${disco_HEADER_DIR}/FixedWidthField")
endif(NOT(EXISTS "${disco_HEADER_DIR}/FixedWidthField"))

# Initialize a variable for collecting utility implementation components
list(APPEND ${projectName}_src) # (empty list)
list(APPEND ${projectName}_src_headers) # (empty list)
list(APPEND ${projectName}_bin_headers) # (empty list)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/disco.hpp.in"
  "${HEADER_DIR}/disco.hpp"
  COPYONLY
  )

set(headers "")
list(APPEND headers
  "FixedWidthField"
  "Record"
  )

foreach(header ${headers})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${header}.hpp.in" 
    "${disco_HEADER_DIR}/${header}.hpp"
    COPYONLY
    )
endforeach(header)

# setup test labels
list(APPEND testLabels disco)

# traverse subdirectories
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/FixedWidthField" )

include(${commonCMakeScripts_path}/terminus.cmake)
