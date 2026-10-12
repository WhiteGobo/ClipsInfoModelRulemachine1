set(basename "ClipsInfoModelRulemachine1::")
set(basepath "${CMAKE_CURRENT_SOURCE_DIR}/data")


#read_manifest("${basepath}/manifest.json" testarray length)

file(READ "${basepath}/manifest.json" MANIFEST_STRING)
string(JSON baseiri
	GET "${MANIFEST_STRING}" baseIri
)
string(JSON testsequence
	GET "${MANIFEST_STRING}" sequence
)
string(JSON length
	LENGTH "${testsequence}"
)

math(EXPR range "${length} - 1")
foreach(x RANGE 0 ${range})
	set(extras "")
	string(JSON data GET "${testsequence}" ${x})
	string(JSON testsuffix GET ${data} name)
	string(JSON premise GET ${data} premise)
	string(JSON query GET ${data} query)
	string(JSON testtype GET ${data} "@type")
	if (testtype MATCHES "NegativeEntailment")
		list(APPEND extras "--expected-failure")
	endif()

	string(JSON entailment ERROR_VARIABLE ignoreError
		GET ${data} entailment)
	if(NOT ${entailment} MATCHES "NOTFOUND")
		string(JSON ent_length LENGTH ${entailment})
		math(EXPR ent_range "${ent_length} - 1")
		foreach(y RANGE 0 ${ent_range})
			set(tmp_extras "${extras}")
			string(JSON ENTAILMENT GET ${entailment} ${y})
			# cut of "http://www.w3.org/ns/entailment/"
			string(SUBSTRING "${ENTAILMENT}" 32 -1 tmp_ent_name)

			set(testname "${basename}${testsuffix}::${tmp_ent_name}")
			set(configured_premise "${CMAKE_CURRENT_BINARY_DIR}/${testsuffix}_${tmp_ent_name}_premise.clp")

			configure_file("${basepath}/${premise}"
					"${configured_premise}")
			add_test(NAME "${testname}"
				COMMAND ClipsInfoModelRulemachine1_testdriver
				ARGS
				"--premise" "${configured_premise}"
				"--conclusion" "${basepath}/${query}"
				"--basepath" "${basepath}"
				"--baseiri" "${baseiri}"
				${extras}
			)
			set_property(TEST "${testname}" PROPERTY LABELS "ClipsInfoModelRulemachine1" "${testtype}")
		endforeach()
	else()
		set(testname "${basename}${testsuffix}")
		add_test(NAME "${testname}" COMMAND ClipsInfoModelRulemachine1_testdriver
			ARGS
			"--premise" "${basepath}/${premise}"
			"--conclusion" "${basepath}/${query}"
			"--basepath" "${basepath}"
			"--baseiri" "${baseiri}"
			${extras}
		)
	endif()
		set_property(TEST "${testname}" PROPERTY LABELS "ClipsInfoModelRulemachine1" "${testtype}")
endforeach()
