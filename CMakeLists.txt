##########################
set(PROJECT_NAME FFTW_extra) 
set(LIB_NAME fftw_extra)
set(EXTERNAL_INCLUDES ../Multi_array/src ./src)

###########################
cmake_minimum_required(VERSION 3.15)
project(%{PROJECT_NAME} VERSION 1.0.0) # Needs to be ontop
include(config.cmake)
string(FIND ${CMAKE_CXX_COMPILER} x86_64-w64-mingw32-g++ IS_MINGW) 

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(IS_MINGW) #Crosscompiling
    set(Python_EXECUTABLE ${CONDA_PY_EXE})
else() #unix
    find_package(Python COMPONENTS Interpreter REQUIRED)
endif()

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/obj)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/obj)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/obj)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/obj)

file(GLOB SRC_FILES "src/*.cpp")

add_compile_options(-Wall -O3 -march=native )

add_library(${LIB_NAME} ${SRC_FILES})

# peparing pybind11 includes
execute_process(COMMAND ${Python_EXECUTABLE} -m pybind11 --includes OUTPUT_VARIABLE PY_INCL)
string(REGEX REPLACE "-I" "" PY_INCL ${PY_INCL}) #removes -I
string(REGEX REPLACE "\n" "" PY_INCL ${PY_INCL}) #removes \n
if(CYGWIN)
string(REGEX REPLACE "C\:" "/cygdrive/c" PY_INCL ${PY_INCL})
endif()

#compile includes
separate_arguments(PY_INCL)
include_directories(${PY_INCL})
separate_arguments(EXTERNAL_INCLUDES)
include_directories(${EXTERNAL_INCLUDES})

#linking 
if ( IS_MINGW ) # genrate libbrary named "name.pyd" else it's named "libname.so"
    set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
    set_target_properties(${LIB_NAME} PROPERTIES SUFFIX ".pyd")
	target_link_libraries(${LIB_NAME} ${CONDA_PY_LINKS})
endif()
target_link_libraries(${LIB_NAME} -lfftw3)


