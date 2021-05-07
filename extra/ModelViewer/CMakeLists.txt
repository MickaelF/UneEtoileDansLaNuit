set(PROJECT_NAME ModelViewer)

project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(UneEtoile_DIR ${CMAKE_SOURCE_DIR}/include)

set(SRCS
    main.cpp
    mainscene.cpp
    basicshader.cpp)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${INCLUDED_LIBS} UneEtoile)
target_include_directories(${PROJECT_NAME} PRIVATE ${UneEtoile_DIR} ${GLM_DIR})

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/shaders
                ${CMAKE_CURRENT_BINARY_DIR}/shaders)