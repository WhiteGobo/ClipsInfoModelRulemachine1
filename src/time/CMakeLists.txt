set(libname ClipsInfoModelRulemachine1_time)

add_library(${libname}
	time.c
	ClipsInfoModelRulemachine1_time.h
)

target_include_directories(${libname} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${libname} PUBLIC
	clips
	AdvancedCDatatypes
)

target_link_libraries(${libname} PRIVATE
	ClipsInfoModelRulemachine1_shared_information
	ClipsInfoModelRulemachine1_literals
	#ClipsInfoModelRulemachine1_externaladdress
	#ClipsInfoModelRulemachine1_data
	#ClipsInfoModelRulemachine1_terms
)
