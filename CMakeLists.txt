cmake_minimum_required(VERSION 3.25)
set(CMAKE_C_FLAGS "-g") #enable lines in memtest

project(ClipsInfoModelRulemachine1 VERSION 0.1.0 LANGUAGES C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(packages.cmake)

set(CACHE{INFO_MODEL_RULEMACHINE1_OFFSET} TYPE STRING
	HELP "Index location of clips environment data"
	VALUE 5)

add_subdirectory(src)

enable_testing()

add_subdirectory(test)
