add_library(ClipsInfoModelRulemachine1_literals
	literals.c
	literals.h
	lexeme.c
	lexeme.h
	datatype_to_internal_representation.c
	datatype_to_internal_representation.h
)

target_link_libraries(ClipsInfoModelRulemachine1_literals PUBLIC
	clips
)

target_link_libraries(ClipsInfoModelRulemachine1_literals PRIVATE
	ClipsInfoModelRulemachine1_shared_information
	ClipsInfoModelRulemachine1_number
	ClipsInfoModelRulemachine1_time
	ClipsInfoModelRulemachine1_string
)

target_include_directories(ClipsInfoModelRulemachine1_literals PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/"
)
