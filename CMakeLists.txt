cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(program VERSION 1.0)

file (GLOB_RECURSE program_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE program_HEADERS CONFIGURE_DEPENDS "src/*.h")

set (program_INCLUDE_DIRS "")
foreach (_headerFile ${program_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND program_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES program_INCLUDE_DIRS)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(app ${program_SOURCES})
target_include_directories(app PRIVATE ${program_INCLUDE_DIRS})
target_link_libraries(app ${SDL2_LIBRARIES})

target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror
								   -fsanitize=address)
target_link_options(app PRIVATE -fsanitize=address)
