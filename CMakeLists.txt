cmake_minimum_required(VERSION 3.21)
project(AncestorTree)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(examples)

enable_testing() #Enable c-tests for testing in GitHub workflows
add_subdirectory(tests) # Ligger egen CMakeLists.txt i mappen tests