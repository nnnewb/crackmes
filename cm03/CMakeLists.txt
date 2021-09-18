find_package(wxWidgets REQUIRED)
find_package(openssl REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(cm03-easy WIN32 main.cpp)
target_compile_options(cm03-easy PRIVATE /Od /Ob0)
target_include_directories(cm03-easy PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(cm03-easy PRIVATE ${wxWidgets_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)

add_executable(cm03-normal WIN32 main.cpp)
target_compile_options(cm03-normal PRIVATE /O1 /Ob0)
target_include_directories(cm03-normal PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(cm03-normal PRIVATE ${wxWidgets_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)

add_executable(cm03-hard WIN32 main.cpp)
target_compile_options(cm03-easy PRIVATE /O2)
target_include_directories(cm03-hard PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(cm03-hard PRIVATE ${wxWidgets_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)

add_executable("cm03-test" "test.cpp")
target_link_libraries("cm03-test" PRIVATE GTest::gtest GTest::gtest_main OpenSSL::SSL OpenSSL::Crypto)
