cmake_minimum_required(VERSION 3.10)

project(ball)

find_package(SFML COMPONENTS graphics REQUIRED)

add_executable(ball
	main.cpp
	src/cpp/Ball.cpp
	src/cpp/Physics.cpp
	src/cpp/Windows.cpp
)

target_link_libraries(ball PUBLIC sfml-graphics)

target_include_directories(ball PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/hpp)

