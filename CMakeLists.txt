########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.16 )
project( disco LANGUAGES CXX )

########################################################################
# Dependencies
########################################################################

include( cmake/disco_dependencies.cmake )

########################################################################
# Project targets
########################################################################

add_library( disco INTERFACE )
target_include_directories( disco INTERFACE src/ )
target_link_libraries( disco
    INTERFACE catch-adapter
    )
