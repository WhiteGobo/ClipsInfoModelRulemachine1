set(libname ClipsInfoModelRulemachine1_externaladdress)

add_library(${libname}
	externaladdress.c
	ClipsInfoModelRulemachine1_externaladdress.h
)

target_include_directories(${libname} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${libname} PUBLIC
	clips
	ClipsInfoModelRulemachine1_list
)
