add_executable(ClipsInfoModelRulemachine1_test_local_values
	test.c
)
target_link_libraries(ClipsInfoModelRulemachine1_test_local_values
	ClipsInfoModelRulemachine1
	RIFImporter
	Mime2Rdf4C
)

set(basepath "${CMAKE_CURRENT_SOURCE_DIR}")
set(baseiri "http://example.com/")
set(premise "premise.clp")
set(testname "ClipsInfoModelRulemachine1::test_local_values")
add_test(NAME "${testname}"
	COMMAND ClipsInfoModelRulemachine1_test_local_values
	"--premise" "${basepath}/${premise}"
	"--basepath" "${basepath}"
	"--baseiri" "${baseiri}"
)
set_property(TEST "${testname}" PROPERTY LABELS "ClipsInfoModelRulemachine1")
