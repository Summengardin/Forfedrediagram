add_executable(NoCLIExample
        NoCLIExample.cpp)

target_include_directories(NoCLIExample
        PUBLIC
        "${CMAKE_SOURCE_DIR}/examples/CLI-Person")