cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
     "src/*.cpp" "src/*.cc")

add_executable(exec ${SOURCE_FILES})
target_include_directories(exec PRIVATE include)

if(APPLE)
    target_link_libraries(exec PRIVATE iconv)
endif()

target_compile_options(exec PRIVATE -Wno-deprecated-declarations)

