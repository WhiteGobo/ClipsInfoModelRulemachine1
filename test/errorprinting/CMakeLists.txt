set(name ClipsInfoModelRulemachine1_test_errorprinting)
add_executable(${name}
	test.c
)
target_link_libraries(${name}
	ClipsInfoModelRulemachine1
	RIFRDFQuery
	Mime2Rdf4C
	ClipsInfoModelRulemachine1_test_reroute2stderr
)


set(testname "ClipsInfoModelRulemachine1::errorprinting")
add_test(NAME "${testname}"
	COMMAND ${name}
)
set_property(TEST "${testname}" PROPERTY LABELS "ClipsInfoModelRulemachine1")
set_property(TEST "${testname}" PROPERTY PASS_REGULAR_EXPRESSION
	"http\:\/\/grep\.this\/uri\#.*\/grep\/this\/path\/"
)
