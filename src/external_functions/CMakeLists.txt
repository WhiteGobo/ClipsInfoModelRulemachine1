add_library(ClipsInfoModelRulemachine1_external_functions
	external_functions.c
	include/external_functions.h
	external_function_list.h
	functions_from_literals.c
	functions_from_literals.h
	is_literal_functions.c
	list_functions.c
	math_functions.c
	literal_functions.c
	string_functions.c
	boolean_functions.c
	formula_functions.c
	time_functions.c
	literal_generator_functions.c
	importexport_functions.c
	helper.c
	helper.h
)

target_link_libraries(ClipsInfoModelRulemachine1_external_functions PRIVATE
	ClipsInfoModelRulemachine1_data
	ClipsInfoModelRulemachine1_shared_information
	ClipsInfoModelRulemachine1_extractor
	ClipsInfoModelRulemachine1_literals
	ClipsInfoModelRulemachine1_list
	ClipsInfoModelRulemachine1_number
	ClipsInfoModelRulemachine1_string
	ClipsInfoModelRulemachine1_time
	bcd47LanguageTagsC

	AdvancedCDatatypes
	GetCurrentTimezonePosixA
)

target_link_libraries(ClipsInfoModelRulemachine1_external_functions PUBLIC
	clips
)

target_include_directories(ClipsInfoModelRulemachine1_external_functions PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
target_include_directories(ClipsInfoModelRulemachine1_external_functions PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/"
)
