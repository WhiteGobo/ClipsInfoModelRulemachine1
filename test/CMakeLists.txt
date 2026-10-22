include(CTest)
add_subdirectory(reroute2stderr)

add_executable(ClipsInfoModelRulemachine1_testdriver
	testa.c
)
target_link_libraries(ClipsInfoModelRulemachine1_testdriver
	ClipsInfoModelRulemachine1
	RIFRDFQuery
	Mime2Rdf4C
	ClipsInfoModelRulemachine1_test_reroute2stderr
)

include(configure-datatest.cmake)

add_subdirectory(test_local_values)
add_subdirectory(errorprinting)
