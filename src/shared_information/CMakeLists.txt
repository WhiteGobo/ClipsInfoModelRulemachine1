set(includepath ${CMAKE_CURRENT_BINARY_DIR})

foreach(x IN ITEMS
		"shared_information.h"
		"namespace_CIMR1.h"
		"namespace_ACT.h"
		"namespace_FUNC.h"
		"namespace_OWL.h"
		"namespace_PRED.h"
		"namespace_RDF.h"
		"namespace_RDFS.h"
		"namespace_RIF.h"
		"namespace_RIFBUILTIN.h"
		"namespace_RIFENTAIL.h"
		"namespace_SYNTAX.h"
		"namespace_XS.h"
)
	configure_file(
		"${CMAKE_CURRENT_SOURCE_DIR}/${x}.in"
		"${includepath}/${x}"
	)
endforeach()

add_library(ClipsInfoModelRulemachine1_shared_information
	shared_information.c
	"${includepath}/shared_information.h"
)

target_link_libraries(ClipsInfoModelRulemachine1_shared_information PUBLIC
	clips
	RIFImporter
	ClipsInfoModelRulemachine1_extractor
)

target_include_directories(ClipsInfoModelRulemachine1_shared_information PUBLIC
	"${includepath}/"
)
