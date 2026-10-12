include(FindPackageHandleStandardArgs)

find_library(clips_LIBRARY
	NAMES clips
)
find_path(clips_INCLUDE_DIR clips.h
	PATH_SUFFIXES clips
)


find_package_handle_standard_args(clips
	REQUIRED_VARS clips_LIBRARY clips_INCLUDE_DIR)


if(NOT clips_LIBRARY)
	message(FATAL_ERROR "clips not found. See README.md for suggestions.")
endif()
#FetchContent_Declare(
#	clips
#	URL https://sourceforge.net/projects/clipsrules/files/CLIPS/6.4.1/clips_core_source_641.zip
#	URL_HASH MD5=3c470a99fa25981d802e63c205c27593
#	)")

if(NOT clips_INCLUDE_DIR)
	message(FATAL_ERROR "clips header missing. clips library was found.")
endif()

mark_as_advanced(clips_LIBRARY)
mark_as_advanced(clips_INCLUDE_DIR)

add_library(clips SHARED IMPORTED)
target_include_directories(clips INTERFACE
	${clips_INCLUDE_DIR}
	#$<BUILD_INTERFACE:${clips_INCLUDE_DIR}>
)
set_property(TARGET clips PROPERTY IMPORTED_LOCATION ${clips_LIBRARY})



#message(FATAL_ERROR "brubru ${clips_INCLUDE_DIR}")


#add_library(clips SHARED IMPORTED)
#set_property(TARGET clips
#	PROPERTY IMPORTED_LOCATION ${clips_library_path})
#target_include_directories(clips INTERFACE
#        $<BUILD_INTERFACE:${CLIPS_INCLUDES}>
#)

