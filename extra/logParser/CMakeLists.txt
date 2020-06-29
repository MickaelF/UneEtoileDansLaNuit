set(SUB_PROJECT_NAME LogParser)

set(SRCS main.cpp
	logParser.cpp
	logParser.h)

add_executable(${SUB_PROJECT_NAME} ${SRCS})