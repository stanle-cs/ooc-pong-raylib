cmake_minimum_required(VERSION 3.0.0)
project(raypongooc LANGUAGES C VERSION 0.1.0)
set(CMAKE_C_STANDARD 11)
file(GLOB source "${PROJECT_SOURCE_DIR}/*.c" "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/subclasses/*.c" "${PROJECT_SOURCE_DIR}/subclasses/*.h")
add_executable(${PROJECT_NAME} ${source})
include_directories(
    ${PROJECT_SOURCE_DIR}/ooc
)

# Adding Raylib
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)


target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
