#rename to datatype encoder

add_library(ClipsInfoModelRulemachine1_terms
	terms.c
	terms.h
	percent_encode.c
	percent_encode.h
)

target_include_directories(ClipsInfoModelRulemachine1_terms PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(ClipsInfoModelRulemachine1_terms PUBLIC
	clips
)

target_link_libraries(ClipsInfoModelRulemachine1_terms PRIVATE
#	ClipsInfoModelRulemachine1_extractor
	ClipsInfoModelRulemachine1_shared_information
	ClipsInfoModelRulemachine1_list
)

add_executable(CIMR1_percent_decode
	CIMR1_percent_decode_exe.c
)

target_link_libraries(CIMR1_percent_decode
	ClipsInfoModelRulemachine1_terms
)
