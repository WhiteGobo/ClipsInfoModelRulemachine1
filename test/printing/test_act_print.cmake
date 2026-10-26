set(name ClipsInfoModelRulemachine1_test_printing_act_print)
add_executable(${name}
	test_act_print.c
)
target_link_libraries(${name}
	ClipsInfoModelRulemachine1
	RIFRDFQuery
	Mime2Rdf4C
	ClipsInfoModelRulemachine1_test_reroute2stderr
)


set(testname "ClipsInfoModelRulemachine1::printing::act_print")
add_test(NAME "${testname}"
	COMMAND ${name}
)
set_property(TEST "${testname}" PROPERTY LABELS "ClipsInfoModelRulemachine1")
set_property(TEST "${testname}" PROPERTY PASS_REGULAR_EXPRESSION
	"testoutput§.*pass"
)
