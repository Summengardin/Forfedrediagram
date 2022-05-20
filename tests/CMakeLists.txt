include_directories(PUBLIC "${CMAKE_SOURCE_DIR}/include")

add_executable(TestTree TestTree.cpp)
add_test(NAME TestTree COMMAND TestTree)

add_executable(TestPerson TestPerson.cpp)
add_test(NAME TestPerson COMMAND TestPerson)

add_executable(TestDate TestDate.cpp)
add_test(NAME TestDate COMMAND TestDate)

add_executable(TestJsonParser TestJsonParser.cpp)
add_test(NAME TestJsonParser COMMAND TestJsonParser)

add_executable(TestHelpers TestHelpers.cpp)
add_test(NAME TestHelpers COMMAND TestHelpers)

