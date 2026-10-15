add_library(ClipsInfoModelRulemachine1_data
	data.c
	data.h
	compare.c
)

target_include_directories(ClipsInfoModelRulemachine1_data PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(ClipsInfoModelRulemachine1_data PUBLIC
	clips
	RIFImporter
)
target_link_libraries(ClipsInfoModelRulemachine1_data PRIVATE
	ClipsInfoModelRulemachine1_extractor
	ClipsInfoModelRulemachine1_shared_information
)
