# Custom path to the LIEF install directory
set(LIEF_DIR CACHE PATH ${CMAKE_INSTALL_PREFIX})

# Directory to 'FindLIEF.cmake'
list(APPEND CMAKE_MODULE_PATH ${LIEF_DIR}/share/LIEF/cmake)

# include 'FindLIEF.cmake'
include(FindLIEF)

# Find LIEF
find_package(LIEF REQUIRED COMPONENTS STATIC) # COMPONENTS: <SHARED | STATIC> - Default: STATIC

add_executable(packer2_loader WIN32 loader.c)
target_compile_options(packer2_loader PRIVATE /GS-)
target_link_options(packer2_loader PRIVATE /NODEFAULTLIB /ENTRY:_start)

add_executable(packer2_packer packer.cpp)
target_compile_options(packer2_packer PRIVATE /FIiso646.h)
target_include_directories(packer2_packer PRIVATE ${LIEF_INCLUDE_DIRS})
set_property(TARGET packer2_packer
        PROPERTY CXX_STANDARD 11
        PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(packer2_packer PRIVATE ${LIEF_LIBRARIES})