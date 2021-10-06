add_subdirectory(packer1)
add_subdirectory(packer2)
add_subdirectory(packer3)
add_subdirectory(packer4)

find_package(wxWidgets REQUIRED)

add_executable(cm04 WIN32 main.cpp)
target_include_directories(cm04 PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(cm04 PRIVATE ${wxWidgets_LIBRARIES})
