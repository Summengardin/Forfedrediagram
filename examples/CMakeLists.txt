
link_libraries(FamilyTree_LIB)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")


add_subdirectory(CLI-Person)
add_subdirectory(NoCLI)

#target_link_libraries(FamilyTree_Example FamilyTree_LIB)
