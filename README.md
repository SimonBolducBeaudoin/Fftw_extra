# FFTW_extra
Adding some features to FFTW.

# Dependencies
    All homebrewed libraries are imported using global imports "#include <library.h> ".
    This means that the library must eather be installed in your environnment's path or that it must be included during compilation and linking. 
    You can edit the "CmakeList.txt" to properly include homebrewed libraries.
    - Homebrewed libraries (available on my github : https://github.com/SimonBolducBeaudoin)
        - Multi_array
    - Other dependencies
        - fftw3
            - Can be installed using your package manager.
        - pybind11
    Pybind11 can be installed using you're python package manager (conda(anaconda env),pip,pacman,...).
    
# Building and compiling
    - Edit config.cmake for your machine (If you are compiling in a different envionnment than your python installation) so that pybind11 can be detected and used.
    - Unix environnment
        - cmake -S . -B ./build
        - cmake --build build/
    - Crosscompiling to for windows (Cygwin or any other)
        Pass the toolchain to cmake.
        - cmake -S . -B ./build -DCMAKE_TOOLCHAIN_FILE=../mingw_toolchain.cmake
        - cmake --build build/

# Building in a second directory
Building in a second directory can be usefull to compile in debug mode for example.
Just modify the -B flags (Build flag) argument 
    - cmake -S . -B ./build_debug
    
# Removing the build directory
    cmake doesn't offer a built-in solution. 
    Best solution is to use rm.
    - rm -R -f build/