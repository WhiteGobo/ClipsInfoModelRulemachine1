set(libname ClipsInfoModelRulemachine1_list)

add_library(${libname}
	list.c
	facts.c
	clipsvalue.c
	ClipsInfoModelRulemachine1_list.h
)

target_include_directories(${libname} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${libname} PUBLIC
	clips
)

target_link_libraries(${libname} PRIVATE
	ClipsInfoModelRulemachine1_externaladdress
	ClipsInfoModelRulemachine1_shared_information
	#ClipsInfoModelRulemachine1_data
	#ClipsInfoModelRulemachine1_terms
)
