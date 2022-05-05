add_executable(NoCLIExample
        no_CLI.cpp)

target_include_directories(NoCLIExample
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include")