cmake_minimum_required(VERSION 3.10)
project(herodb)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/third_party)

add_executable(herodb-server src/server/main.cc)
target_link_libraries(herodb-server pthread)

add_executable(herodb-shell src/shell/main.cc)
target_link_libraries(herodb-shell pthread)

add_executable(herodb-router src/router/main.cc)
target_link_libraries(herodb-router pthread)
