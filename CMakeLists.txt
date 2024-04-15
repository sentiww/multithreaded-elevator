cmake_minimum_required(VERSION 3.27)
project(elevator)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

include_directories(include)

add_executable(elevator main.cpp
        src/elevator.cpp
        src/person.cpp
        src/simulation_state.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

target_link_libraries(elevator ${CURSES_LIBRARIES})

file(GLOB SRC_FILES
    "src/*.cpp"
)

file (GLOB HEADERS
    "include/*.h"
)

target_sources(elevator PUBLIC
    ${SRC_FILES}
    ${HEADERS}
)