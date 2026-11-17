add_library(ClipsInfoModelRulemachine1_data_importer
	ClipsInfoModelRulemachine1_data_importer.h
	importer.c
	callback.c
	callback.h
	rifidata.c
)

target_include_directories(ClipsInfoModelRulemachine1_data_importer PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(ClipsInfoModelRulemachine1_data_importer PUBLIC
	clips
	RIFImporter
	Mime2Rdf4C
)

target_link_libraries(ClipsInfoModelRulemachine1_data_importer PRIVATE
	ClipsInfoModelRulemachine1_shared_information
	ClipsInfoModelRulemachine1_data
	ClipsInfoModelRulemachine1_literals
	ClipsInfoModelRulemachine1_list
	ClipsInfoModelRulemachine1_localnode
	cwalk
	DataloaderRDF
	Mime2Rdf4C
)
