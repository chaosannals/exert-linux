file(GLOB PTHRDEMO_SOURCES "*.cpp")

add_executable(pthrdemo)

target_sources(
	pthrdemo
	PRIVATE ${PTHRDEMO_SOURCES}	
)
