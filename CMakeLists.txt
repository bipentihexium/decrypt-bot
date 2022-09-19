cmake_minimum_required(VERSION 3.14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/)

project(DecryptBot VERSION 1.0 DESCRIPTION "<DecryptBot desc>")

add_subdirectory(libs/DPP)

add_executable(decrypt-bot
	./src/main.cpp ./src/command_parser.cpp ./src/math.cpp
)
target_link_libraries(decrypt-bot dpp)
target_include_directories(decrypt-bot PRIVATE ./libs/DPP/include)
set_target_properties(decrypt-bot PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)
