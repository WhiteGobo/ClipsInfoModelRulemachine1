add_library(ClipsInfoModelRulemachine1_string
	ClipsInfoModelRulemachine1_string.h
	strings.c
	percent_encoder.c
	replace.c
)

target_include_directories(ClipsInfoModelRulemachine1_string PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/"
)
