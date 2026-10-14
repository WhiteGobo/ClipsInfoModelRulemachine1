set(libname ClipsInfoModelRulemachine1_localnode)

add_library(${libname}
	ClipsInfoModelRulemachine1_localnode.h
	clipsvalue_map.c
	localnode.c
)

target_include_directories(${libname} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${libname} PUBLIC
	clips
	ClipsInfoModelRulemachine1_literals
)

target_link_libraries(${libname} PRIVATE
	hashtable
)
