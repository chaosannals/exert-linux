file(GLOB PROCDEMO_SOURCES "*.cpp")

add_executable(procdemo)

target_sources(
	procdemo
	PRIVATE ${PROCDEMO_SOURCES}	
)
