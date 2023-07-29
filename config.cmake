set(CMAKE_BUILD_PARALLEL_LEVEL 4)

# Mingw only variables
# Edit depending on your machine
# If Python is present in the compiling environnement the CONDA_PY_EXE and CONDA_PY_LINKS won't be used.
set(CONDA_PY_EXE "C:/Anaconda2/python")
set(CONDA_PY_LINKS "-LC:/Anaconda2/ -lpython27")
if(CYGWIN)
string(REGEX REPLACE "C\:" "/cygdrive/c" CONDA_PY_EXE ${CONDA_PY_EXE})
string(REGEX REPLACE "C\:" "/cygdrive/c" CONDA_PY_LINKS ${CONDA_PY_LINKS})
endif()

