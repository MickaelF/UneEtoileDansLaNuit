set(SUB_PROJECT_NAME LogParser)

set(SRCS main.cpp
	logparser.cpp
	logparser.h)

add_executable(${SUB_PROJECT_NAME} ${SRCS})
