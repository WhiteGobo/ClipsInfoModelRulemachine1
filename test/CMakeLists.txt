include(CTest)

add_executable(ClipsInfoModelRulemachine1_testdriver
	testa.c
)
target_link_libraries(ClipsInfoModelRulemachine1_testdriver
	ClipsInfoModelRulemachine1
	RIFRDFQuery
	Mime2Rdf4C
)

include(configure-datatest.cmake)

add_subdirectory(test_local_values)
