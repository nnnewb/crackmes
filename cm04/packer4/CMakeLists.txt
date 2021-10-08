# set loader properties
add_executable(packer4_loader loader.cpp)
set_property(TARGET packer4_loader PROPERTY CXX_STANDARD 14 PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_options(packer4_loader PRIVATE /GS-)
target_link_libraries(packer4_loader PRIVATE)
target_link_options(packer4_loader PRIVATE /NODEFAULTLIB /ENTRY:_start)

# find LIEF
set(LIEF_DIR CACHE PATH ${CMAKE_INSTALL_PREFIX}) # Custom path to the LIEF install directory
list(APPEND CMAKE_MODULE_PATH ${LIEF_DIR}/share/LIEF/cmake) # Directory to 'FindLIEF.cmake'
include(FindLIEF) # include 'FindLIEF.cmake'
find_package(LIEF REQUIRED COMPONENTS STATIC) # COMPONENTS: <SHARED | STATIC> - Default: STATIC # Find LIEF

# set packer properties
add_executable(packer4_packer packer.cpp)
set_property(TARGET packer4_packer PROPERTY CXX_STANDARD 14 PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_options(packer4_packer PRIVATE /FIiso646.h)
target_include_directories(packer4_packer PRIVATE ${LIEF_INCLUDE_DIRS})
target_link_libraries(packer4_packer PRIVATE ${LIEF_LIBRARIES})
