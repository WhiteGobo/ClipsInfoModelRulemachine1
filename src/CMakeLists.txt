set(includepath ${CMAKE_CURRENT_BINARY_DIR})

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/ClipsInfoModelRulemachine1.h.in"
	"${includepath}/ClipsInfoModelRulemachine1.h"
)

add_subdirectory(shared_information)
add_subdirectory(data)
add_subdirectory(terms)
add_subdirectory(extractor)
add_subdirectory(external_functions)
add_subdirectory(literals)
add_subdirectory(list)
add_subdirectory(clipsexternaladdress)
add_subdirectory(number)
add_subdirectory(string)
add_subdirectory(time)

add_library(ClipsInfoModelRulemachine1
	extract_data.c
	register.c
	templates.c
	"${includepath}/ClipsInfoModelRulemachine1.h"
)

target_include_directories(ClipsInfoModelRulemachine1 PUBLIC
	"${includepath}/"
)

target_link_libraries(ClipsInfoModelRulemachine1 PUBLIC
	clips
)

target_link_libraries(ClipsInfoModelRulemachine1 PRIVATE
	ClipsInfoModelRulemachine1_extractor
	ClipsInfoModelRulemachine1_shared_information
	Mime2Rdf4C
	ClipsInfoModelRulemachine1_external_functions
)

