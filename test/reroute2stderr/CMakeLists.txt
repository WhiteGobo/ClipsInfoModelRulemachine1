set(name "ClipsInfoModelRulemachine1_test_reroute2stderr")
add_library(${name}
	reroute2stderr.c
	reroute2stderr.h
)

target_link_libraries(${name} PUBLIC
	clips
)

target_include_directories(${name} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/"
)
