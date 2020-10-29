#######################################################################
# Setup
#######################################################################

message( STATUS "Adding disco unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/disco/FixedWidthField/Character/test )
add_subdirectory( src/disco/FixedWidthField/ColumnPosition/test )
add_subdirectory( src/disco/FixedWidthField/Integer/test )
add_subdirectory( src/disco/FixedWidthField/Real/ENDF/test )
add_subdirectory( src/disco/FixedWidthField/Real/FixedPoint/test )
add_subdirectory( src/disco/FixedWidthField/Real/Scientific/test )
add_subdirectory( src/disco/FixedWidthField/Real/test )
add_subdirectory( src/disco/Record/test )
