#cmake version
cmake_minimum_required(VERSION 3.10)

#need to input installation directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR (NOT IS_ABSOLUTE ${CMAKE_INSTALL_PREFIX}))
	message(FATAL_ERROR "Define the installation directory (CMAKE_INSTALL_PREFIX) in command line")
endif()

#set C++ standard
set (CMAKE_CXX_STANDARD 11)

# Find default python libraries and interpreter
find_package(PythonInterp EXACT 3 REQUIRED)
find_package(PythonLibs EXACT 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIR})
find_package(Boost EXACT 1.65.1 COMPONENTS python3 REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
set(CMAKE_SHARED_MODULE_SUFFIX ".so")
set(CMAKE_SHARED_MODULE_PREFIX "")

# Build and link the wrapper module
add_library(gamewrapper MODULE src/C++/game.cpp src/C++/gamewrapper.cpp)
target_link_libraries(gamewrapper ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(gamewrapper PRIVATE ${PYTHON_INCLUDE_DIRS} include)


install(PROGRAMS ${PROJECT_BINARY_DIR}/gamewrapper.so DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES src/Python3/gamedisp.py DESTINATION ${CMAKE_INSTALL_PREFIX})

