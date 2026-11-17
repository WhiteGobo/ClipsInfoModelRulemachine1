set(basename "ClipsInfoModelRulemachine1::import::")

add_executable(ClipsInfoModelRulemachine1_test_import_testa
	testa.c
)

target_link_libraries(ClipsInfoModelRulemachine1_test_import_testa
	ClipsInfoModelRulemachine1
	ClipsInfoModelRulemachine1_data_importer
	ClipsInfoModelRulemachine1_test_reroute2stderr
)

set(testname "${basename}testa")
add_test(NAME "${testname}"
	COMMAND ClipsInfoModelRulemachine1_test_import_testa
)
set_property(TEST "${testname}" PROPERTY LABELS "ClipsInfoModelRulemachine1")
