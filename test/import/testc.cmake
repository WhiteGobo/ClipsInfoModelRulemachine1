set(basename "ClipsInfoModelRulemachine1::import::")
set(basepath "${CMAKE_CURRENT_SOURCE_DIR}/")

add_executable(ClipsInfoModelRulemachine1_test_import_testc
	testc.c
)

target_link_libraries(ClipsInfoModelRulemachine1_test_import_testc
	ClipsInfoModelRulemachine1
	ClipsInfoModelRulemachine1_data_importer
	ClipsInfoModelRulemachine1_test_reroute2stderr
)

set(testname "${basename}testc")
add_test(NAME "${testname}"
	COMMAND ClipsInfoModelRulemachine1_test_import_testc
	ARGS
	"--basepath" "${basepath}"
)
set_property(TEST "${testname}" PROPERTY LABELS "ClipsInfoModelRulemachine1")
