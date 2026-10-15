add_library(ClipsInfoModelRulemachine1_extractor
	extractor.h
	extractor.c
	assert_formulas.c
	rifi2clips.c
	userfunction_myimport.c
)

target_include_directories(ClipsInfoModelRulemachine1_extractor PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(ClipsInfoModelRulemachine1_extractor PUBLIC
	clips
	RIFImporter
	Mime2Rdf4C
)

target_link_libraries(ClipsInfoModelRulemachine1_extractor PRIVATE
	ClipsInfoModelRulemachine1_shared_information
	ClipsInfoModelRulemachine1_data
	ClipsInfoModelRulemachine1_literals
	ClipsInfoModelRulemachine1_list
	ClipsInfoModelRulemachine1_localnode
	cwalk
	DataloaderRDF
)
