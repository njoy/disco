
cmake_minimum_required( VERSION 3.2 )
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported configuration types" FORCE )
        
if ( NOT GIT_EXECUTABLE )
    find_package( Git 2.1 )
    if ( NOT GIT_FOUND )
        message( FATAL_ERROR "git installation was not found." )
    endif()
endif()

if( NOT ROOT_DIRECTORY )
    set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    if ( NOT fetched_subprojects )
        if ( NOT PYTHON_EXECUTABLE )
            find_package( PythonInterp 3.4 )
            if ( NOT PYTHONINTERP_FOUND )
                message( FATAL_ERROR "Python interpreter installation was not found." )
            endif()
        endif()
        execute_process( COMMAND ${PYTHON_EXECUTABLE} "./metaconfigure/fetch_subprojects.py"
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                         RESULT_VARIABLE fetch_failure )
        if ( NOT fetch_failure )
            set( fetched_subprojects TRUE CACHE BOOL "fetch script ran" )
        else()
            message( FATAL_ERROR "Failed to fetch dependencies" )
        endif()
    endif()
endif()

if( NOT is_subproject )
    if( NOT ROOT_DIRECTORY )
        set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    endif()
    if ( NOT PYTHON_EXECUTABLE )
        find_package( PythonInterp )
        if ( NOT PYTHONINTERP_FOUND )
            message( FATAL_ERROR "Python interpreter installation was not found." )
        endif()
    endif()
    execute_process( COMMAND ${PYTHON_EXECUTABLE} ./metaconfigure/signature.py ${CMAKE_BINARY_DIR}/signature
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE signature_failure )
    file( READ "${CMAKE_BINARY_DIR}/signature.json" SIGNATURE )
endif()

project( disco LANGUAGES CXX )
get_directory_property( is_subproject PARENT_DIRECTORY )
include( CMakeDependentOption REQUIRED )

set( disco_AppleClang_minimum_version 8.0 )
set( disco_GNU_minimum_version 6.2 )
set( disco_Clang_minimum_version 3.8 )

if( disco_${CMAKE_CXX_COMPILER_ID}_minimum_version )
    if( CMAKE_CXX_COMPILER_VERSION AND
        CMAKE_CXX_COMPILER_VERSION VERSION_LESS
        ${disco_${CMAKE_CXX_COMPILER_ID}_minimum_version} )
        message( FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} version must be greater than ${disco_${CMAKE_CXX_COMPILER_ID}_minimum_version}" )
    endif()
endif()

# general properties
option( disco_strict "Compile time warnings are converted to errors" ON )

# binary instrumentation
option( coverage "Enable binary instrumentation to collect test coverage information in the DEBUG configuration" )
option( profile_generate "Enable binary instrumentation to generation execution profiles in the RELEASE configuration which may be used to guide later optimization" )

# additional optimizations
option( link_time_optimization "Enable link time optimization in the RELEASE configuration" )
option( profile_use "In the RELEASE configuration, leverage previously generated execution profile to inform optimization decisions" )
option( nonportable_optimization "Enable optimizations which compromise portability of resulting binary in the RELEASE configuration" )

# libraries and linking
option( static "Statically link component and environment libraries" OFF )
if ( static AND ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" ) )
    message( FATAL_ERROR "Static binaries not supported on OSX" )
endif()

CMAKE_DEPENDENT_OPTION( static_libraries "Statically link component libraries" OFF "NOT static" ON )

option( unit_tests "Compile the disco unit tests and integrate with ctest" ON ) 

if ( profile_generate AND profile_use )
    message( FATAL_ERROR "Cannot both generate and use execution profile in the same configuration" )
endif()

if ( profile_generate )
    file( MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/profiling" )
endif()

set( disco_AppleClang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_AppleClang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( disco_AppleClang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_AppleClang_Darwin_strict_flags "-Werror" )
set( disco_AppleClang_Darwin_coverage_flags "--coverage" )
set( disco_AppleClang_Darwin_subproject_flags  )
set( disco_AppleClang_Darwin_base_project_flags  )
set( disco_AppleClang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_AppleClang_Darwin_link_time_optimization_flags "-flto" )
set( disco_AppleClang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_AppleClang_Darwin_nonportable_optimization_flags "-march=native" )
set( disco_AppleClang_Darwin_static_flags "-static" )
set( disco_GNU_Linux_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_GNU_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( disco_GNU_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_GNU_Linux_strict_flags "-Werror" )
set( disco_GNU_Linux_coverage_flags "--coverage" )
set( disco_GNU_Linux_subproject_flags  )
set( disco_GNU_Linux_base_project_flags  )
set( disco_GNU_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_Linux_link_time_optimization_flags "-flto" )
set( disco_GNU_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_Linux_nonportable_optimization_flags "-march=native" )
set( disco_GNU_Linux_static_flags "-static" )
set( disco_GNU_Darwin_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_GNU_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( disco_GNU_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_GNU_Darwin_strict_flags "-Werror" )
set( disco_GNU_Darwin_coverage_flags "--coverage" )
set( disco_GNU_Darwin_subproject_flags  )
set( disco_GNU_Darwin_base_project_flags  )
set( disco_GNU_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_Darwin_link_time_optimization_flags "-flto" )
set( disco_GNU_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_Darwin_nonportable_optimization_flags "-march=native" )
set( disco_GNU_Darwin_static_flags "-static" )
set( disco_GNU_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_GNU_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( disco_GNU_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_GNU_MinGW_strict_flags "-Werror" )
set( disco_GNU_MinGW_coverage_flags "--coverage" )
set( disco_GNU_MinGW_subproject_flags  )
set( disco_GNU_MinGW_base_project_flags  )
set( disco_GNU_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_MinGW_link_time_optimization_flags "-flto" )
set( disco_GNU_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_MinGW_nonportable_optimization_flags "-march=native" )
set( disco_GNU_MinGW_static_flags "-static" )
set( disco_GNU_Windows_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_GNU_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( disco_GNU_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_GNU_Windows_strict_flags "-Werror" )
set( disco_GNU_Windows_coverage_flags "--coverage" )
set( disco_GNU_Windows_subproject_flags  )
set( disco_GNU_Windows_base_project_flags  )
set( disco_GNU_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_Windows_link_time_optimization_flags "-flto" )
set( disco_GNU_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_Windows_nonportable_optimization_flags "-march=native" )
set( disco_GNU_Windows_static_flags "-static" )
set( disco_GNU_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++17" )
set( disco_GNU_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( disco_GNU_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_GNU_CYGWIN_strict_flags "-Werror" )
set( disco_GNU_CYGWIN_coverage_flags "--coverage" )
set( disco_GNU_CYGWIN_subproject_flags  )
set( disco_GNU_CYGWIN_base_project_flags  )
set( disco_GNU_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_CYGWIN_link_time_optimization_flags "-flto" )
set( disco_GNU_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_GNU_CYGWIN_nonportable_optimization_flags "-march=native" )
set( disco_GNU_CYGWIN_static_flags "-static" )
set( disco_Clang_Linux_common_flags "-stdlib=libstdc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_Clang_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( disco_Clang_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_Clang_Linux_strict_flags "-Werror" )
set( disco_Clang_Linux_coverage_flags "--coverage" )
set( disco_Clang_Linux_subproject_flags  )
set( disco_Clang_Linux_base_project_flags  )
set( disco_Clang_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_Linux_link_time_optimization_flags "-flto" )
set( disco_Clang_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_Linux_nonportable_optimization_flags "-march=native" )
set( disco_Clang_Linux_static_flags "-static" )
set( disco_Clang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_Clang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( disco_Clang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_Clang_Darwin_strict_flags "-Werror" )
set( disco_Clang_Darwin_coverage_flags "--coverage" )
set( disco_Clang_Darwin_subproject_flags  )
set( disco_Clang_Darwin_base_project_flags  )
set( disco_Clang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_Darwin_link_time_optimization_flags "-flto" )
set( disco_Clang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_Darwin_nonportable_optimization_flags "-march=native" )
set( disco_Clang_Darwin_static_flags "-static" )
set( disco_Clang_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_Clang_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( disco_Clang_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_Clang_MinGW_strict_flags "-Werror" )
set( disco_Clang_MinGW_coverage_flags "--coverage" )
set( disco_Clang_MinGW_subproject_flags  )
set( disco_Clang_MinGW_base_project_flags  )
set( disco_Clang_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_MinGW_link_time_optimization_flags "-flto" )
set( disco_Clang_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_MinGW_nonportable_optimization_flags "-march=native" )
set( disco_Clang_MinGW_static_flags "-static" )
set( disco_Clang_Windows_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( disco_Clang_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( disco_Clang_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_Clang_Windows_strict_flags "-Werror" )
set( disco_Clang_Windows_coverage_flags "--coverage" )
set( disco_Clang_Windows_subproject_flags  )
set( disco_Clang_Windows_base_project_flags  )
set( disco_Clang_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_Windows_link_time_optimization_flags "-flto" )
set( disco_Clang_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_Windows_nonportable_optimization_flags "-march=native" )
set( disco_Clang_Windows_static_flags "-static" )
set( disco_Clang_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++17" )
set( disco_Clang_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( disco_Clang_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( disco_Clang_CYGWIN_strict_flags "-Werror" )
set( disco_Clang_CYGWIN_coverage_flags "--coverage" )
set( disco_Clang_CYGWIN_subproject_flags  )
set( disco_Clang_CYGWIN_base_project_flags  )
set( disco_Clang_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_CYGWIN_link_time_optimization_flags "-flto" )
set( disco_Clang_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( disco_Clang_CYGWIN_nonportable_optimization_flags "-march=native" )
set( disco_Clang_CYGWIN_static_flags "-static" )
get_directory_property( is_subproject PARENT_DIRECTORY )

if( NOT TARGET catch-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/catch-adapter )
endif()


if ( NOT GIT_EXECUTABLE )
    find_package( Git )
    if ( NOT GIT_FOUND )
        message( FATAL_ERROR "git installation was not found." )
    endif()
endif()

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
) 

message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )
message( STATUS "" )
message( STATUS "disco" )
message( STATUS "Git current branch: ${GIT_BRANCH}" )
message( STATUS "Git commit hash: ${GIT_HASH}" )
message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )

add_library( disco INTERFACE )
target_sources( disco INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src/disco.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/Record.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Integer.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/ColumnPosition.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/noDigits.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Character.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/ENDF.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Exponentiation.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Scientific.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/FixedPoint.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Pow.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/ENDF/src/write.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/FixedPoint/src/write.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Scientific/src/writeWithConsumption.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Scientific/src/writeWithoutConsumption.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Scientific/src/writeInvalid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Scientific/src/writeInfinity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Scientific/src/writeZero.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/Scientific/src/write.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/src/parseBase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/src/parseExponent.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/src/noDigits.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/src/parseSign.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/src/parseInfinity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Real/src/parseFraction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Character/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Character/src/write.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/ColumnPosition/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/ColumnPosition/src/write.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Integer/src/parseInteger.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Integer/src/writeInvalid.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Integer/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/Integer/src/write.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/FixedWidthField/src/whiteSpace.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/disco/src/noDigits.hpp" )

target_include_directories( disco INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/src src/ )

set( PREFIX disco_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME} )

target_link_libraries( disco INTERFACE "$<$<AND:$<CONFIG:RELEASE>,$<BOOL:${link_time_optimization}>>:${${PREFIX}_RELEASE_flags};${${PREFIX}_link_time_optimization_flags}$<$<BOOL:${profile_generate}>:${${PREFIX}_profile_generate_flags};>$<$<BOOL:${profile_use}>:${${PREFIX}_profile_use_flags};>$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags};>>$<$<CONFIG:DEBUG>:$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags};>>$<$<BOOL:CXX_appended_flags>:${CXX_appended_flags};>$<$<BOOL:disco_appended_flags>:${disco_appended_flags};>" )

target_link_libraries( disco INTERFACE catch-adapter )

if( NOT is_subproject )
    enable_testing() 
    if ( unit_tests )
        add_subdirectory( src/disco/FixedWidthField/Character/test )
        add_subdirectory( src/disco/FixedWidthField/ColumnPosition/test )
        add_subdirectory( src/disco/FixedWidthField/Integer/test )
        add_subdirectory( src/disco/FixedWidthField/Real/test )
        add_subdirectory( src/disco/FixedWidthField/Real/ENDF/test )
        add_subdirectory( src/disco/FixedWidthField/Real/FixedPoint/test )
        add_subdirectory( src/disco/FixedWidthField/Real/Scientific/test )
        add_subdirectory( src/disco/Record/test )
    endif() 
endif()

install( FILES "${CMAKE_BINARY_DIR}/signature.json"
         DESTINATION share/${CMAKE_PROJECT_NAME}
         PERMISSIONS OWNER_READ OWNER_WRITE
                     GROUP_READ
                     WORLD_READ
)
install( DIRECTORY src// DESTINATION include
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                          GROUP_READ
                          WORLD_READ
         DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE
                               GROUP_READ
                               WORLD_READ
         FILES_MATCHING REGEX ".*\.h[+][+]$|.*\.hxx$|.*\.hpp$|.*\.hh$|.*\.h$"  )

                    INCLUDE(CPack)
                    