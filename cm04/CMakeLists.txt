# Custom path to the LIEF install directory
set(LIEF_DIR CACHE PATH ${CMAKE_INSTALL_PREFIX})

# Directory to 'FindLIEF.cmake'
list(APPEND CMAKE_MODULE_PATH ${LIEF_DIR}/share/LIEF/cmake)

# include 'FindLIEF.cmake'
include(FindLIEF)

# Find LIEF
find_package(LIEF REQUIRED COMPONENTS STATIC) # COMPONENTS: <SHARED | STATIC> - Default: STATIC

find_package(wxWidgets REQUIRED)

add_executable(cm04 WIN32 main.cpp)
target_include_directories(cm04 PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(cm04 PRIVATE ${wxWidgets_LIBRARIES})
if(${CMAKE_BUILD_TYPE} MATCHES Release|RelWithDeb)
	target_compile_options(cm04 PRIVATE /MD /Wall)
elseif(${CMAKE_BUILD_TYPE} MATCHES Debug)
	target_compile_options(cm04 PRIVATE /MDd /Wall)
endif()

add_executable(loader loader.c)

add_executable(loader_2 WIN32 loader_2.c)
target_compile_options(loader_2 PRIVATE /GS-)
target_link_options(loader_2 PRIVATE /NODEFAULTLIB /ENTRY:_start)

add_executable(packer packer.cpp)
if(MSVC)
	target_compile_options(packer PRIVATE /FIiso646.h /MT)
	set_property(TARGET packer PROPERTY LINK_FLAGS /NODEFAULTLIB:MSVCRT)
endif()
target_include_directories(packer PRIVATE ${LIEF_INCLUDE_DIRS})
set_property(TARGET packer
			PROPERTY CXX_STANDARD 11
			PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(packer PRIVATE ${LIEF_LIBRARIES})
