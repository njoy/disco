project( disco )

if( NOT DEFINED disco_DEPENDENCIES )
    set( disco_DEPENDENCIES TRUE )
endif()

add_library( disco INTERFACE )
target_include_directories( disco INTERFACE src/ )
target_link_libraries( disco INTERFACE catch-adapter )
