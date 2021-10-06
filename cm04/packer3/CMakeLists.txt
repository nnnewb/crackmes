# Custom path to the LIEF install directory
set(LIEF_DIR CACHE PATH ${CMAKE_INSTALL_PREFIX})

# Directory to 'FindLIEF.cmake'
list(APPEND CMAKE_MODULE_PATH ${LIEF_DIR}/share/LIEF/cmake)

# include 'FindLIEF.cmake'
include(FindLIEF)

# Find LIEF
find_package(LIEF REQUIRED COMPONENTS STATIC) # COMPONENTS: <SHARED | STATIC> - Default: STATIC

add_executable(packer3_packer compress_packer.cpp)
if (MSVC)
    target_compile_options(packer3_packer PRIVATE /FIiso646.h)
endif ()
target_include_directories(packer3_packer PRIVATE ${LIEF_INCLUDE_DIRS})
set_property(TARGET packer3_packer PROPERTY CXX_STANDARD 14 PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(packer3_packer PRIVATE ${LIEF_LIBRARIES} Cabinet.lib)

add_executable(packer3_loader WIN32 compress_loader.cpp)
set_property(TARGET packer3_loader PROPERTY CXX_STANDARD 14 PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_options(packer3_loader PRIVATE /GS-)
target_link_libraries(packer3_loader PRIVATE Cabinet.lib)
target_link_options(packer3_loader PRIVATE /NODEFAULTLIB /ENTRY:_start Cabinet.lib)
