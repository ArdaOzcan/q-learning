cmake_minimum_required(VERSION 3.19.2)

project(qlearning)
find_package(SFML 2.5.1 COMPONENTS system graphics audio network REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(qlearning PRIVATE sfml-audio sfml-graphics sfml-network sfml-system)

