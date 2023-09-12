# Should be compatible with unix and 
# compilation on windows using cygwin and crosscompiling using mingw
# also don't forget to edit config.cmake for machine specific stuff     

set(PROJECT_NAME FFTW_extra)                    
set(LIB_NAME fftw_extra)                        
set(EXTERNAL_INCLUDES ../Multi_array/src ./src) 
separate_arguments(EXTERNAL_INCLUDES)           # Turned into a list a list 
set(COMPILE_OPTIONS_ADD )  
set(LINKS -lfftw3)       

cmake_minimum_required(VERSION 3.15)
project(${PROJECT_NAME} ) # Needs to be ontop

# AUTOGIT STUFF #########
include(../AutoGitVersion/AutoGitVersion.cmake) # Defined cmake functions : AutoGitVersion and others
AutoGitVersion()                 # Sets up a target git_version.cpp that constains  kGitHash and GitTag as const
set(DEPENDS_ON_GIT_VERSION git_version)
#########################

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/obj)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/obj)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/obj)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/obj)

file(GLOB SRC_FILES_PY "src/*_py.cpp")

file(GLOB SRC_FILES "src/*.cpp")
set(SRC_STATIC ${SRC_FILES})
list(FILTER SRC_STATIC EXCLUDE REGEX ".*_py\\.cpp$")
list(FILTER SRC_STATIC EXCLUDE REGEX ".*python_submodule\\.cpp$")

add_compile_options(-Wall -O3 -march=native )
add_compile_options(${COMPILE_OPTIONS_ADD})

add_library(${LIB_NAME}_py ${SRC_FILES})        #shared library (i.e. the python library)
set_target_properties(${LIB_NAME}_py PROPERTIES OUTPUT_NAME ${LIB_NAME})        #shared library (i.e. the python library)
add_library(${LIB_NAME} STATIC ${SRC_STATIC}) #static library (i.e. to import in other c++ projects)
include(config.cmake) # sets IS_MINGW,PY_INCL,SHARED_LIB_PREFIX,SHARED_LIB_SUFFIX and updates LINKS

#compile includes
include_directories(${PY_INCL})           # pybind11 includes
include_directories(${EXTERNAL_INCLUDES})

#linking 
set_target_properties(${LIB_NAME}_py PROPERTIES PREFIX "${SHARED_LIB_PREFIX}")
set_target_properties(${LIB_NAME}_py PROPERTIES SUFFIX ${SHARED_LIB_SUFFIX})
target_link_libraries(${LIB_NAME}_py ${DEPENDS_ON_GIT_VERSION} ${LINKS})
set_target_properties(${LIB_NAME} PROPERTIES PREFIX "${SHARED_LIB_PREFIX}")
target_link_libraries(${LIB_NAME} ${LINKS})


