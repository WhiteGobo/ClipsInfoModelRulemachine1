set(index 0)
foreach(inout_strings IN ITEMS
		"<http://example.com/help>;<http://example.com/help>"
		"\"Hello world@\";\"Hello%20world%40\""
		"\"Hello world\"@en;\"Hello%20world@@en\""
		"\"Hello world\"@;\"Hello%20world@@\""
		"\"Hello world@\"^^rdf:PlainLiteral;\"Hello%20world%40\\^\\^http://www.w3.org/1999/02/22-rdf-syntax-ns#PlainLiteral\""
		"\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz/+0123456789\"^^xs:string;\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz%2F%2B0123456789\\^\\^http://www.w3.org/2001/XMLSchema#string\""
		"ex:ok;<http://example.org/example#ok>"
		"func:count;<http://www.w3.org/2007/rif-builtin-function#count>"
		"\"P3DT2H\"^^xs:dayTimeDuration;\"P3DT2H\\^\\^http://www.w3.org/2001/XMLSchema#dayTimeDuration\""
)
	list(GET inout_strings 0 in_string)
	list(GET inout_strings 1 out_string)
	set(testname "ClipsInfoModelRulemachine1::test_decode::${index}")
	add_test(NAME "${testname}"
		COMMAND "$<TARGET_FILE:CIMR1_percent_decode>"
		"${in_string}"
	)

	set_property (TEST "${testname}"
		      PROPERTY PASS_REGULAR_EXPRESSION "${out_string}")
	math(EXPR index "${index} + 1")
endforeach()
