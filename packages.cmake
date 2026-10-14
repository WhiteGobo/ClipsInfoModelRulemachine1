find_package(clips REQUIRED)

include(FetchContent)

#FetchContent_Declare(
#	CInterfaceOxJsonld
#	GIT_REPOSITORY https://github.com/WhiteGobo/CInterfaceOxJsonld.git
#	#GIT_TAG 6ae08cf54ec74aa5f8a9d0ca8547155af53be03a
#	FIND_PACKAGE_ARGS
#)
#FetchContent_MakeAvailable(CInterfaceOxJsonld)

FetchContent_Declare(
	hashtable
	GIT_REPOSITORY https://github.com/WhiteGobo/hashtable
        CMAKE_CACHE_ARGS -DBUILD_SHARED_LIBS=OFF
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(hashtable)


FetchContent_Declare(
	bcd47LanguageTagsC
	GIT_REPOSITORY https://github.com/WhiteGobo/bcd47LanguageTagsC.git
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(bcd47LanguageTagsC)

FetchContent_Declare(
	RIFImporter
	GIT_REPOSITORY https://github.com/WhiteGobo/RIFImporter.git
	FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(RIFImporter)

FetchContent_Declare(
	RIFRDFQuery
	GIT_REPOSITORY https://github.com/WhiteGobo/RIFRDFQuery.git
        OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(RIFRDFQuery)

FetchContent_Declare(
	DataloaderRDF
	GIT_REPOSITORY https://github.com/WhiteGobo/DataloaderRDF.git
        OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(DataloaderRDF)

FetchContent_Declare(
        cwalk
        GIT_REPOSITORY https://github.com/likle/cwalk.git
	GIT_TAG v1.2.9
	FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(cwalk)

FetchContent_Declare(
	Mime2Rdf4C
	GIT_REPOSITORY https://github.com/WhiteGobo/Mime2Rdf4C.git
	#GIT_TAG 8b244ca1826c024a641d98f0bb52e3c649e79972
	FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(Mime2Rdf4C)

FetchContent_Declare(
	AdvancedCDatatypes
	GIT_REPOSITORY https://github.com/WhiteGobo/AdvancedCDatatypes.git
	#GIT_TAG 8b244ca1826c024a641d98f0bb52e3c649e79972
	FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(AdvancedCDatatypes)
