# FFTW_extra
Adding some features to FFTW.

# Output
    - *.pyd a python library containing the wrapped code.
    - *.a   a static labrary excluding the python features (only c/c++ code).
    
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

# Removing AutoGitVersion
    AutoGitVersion automatically collects information about the current git commit and saves them in a litteral string (kGitInfo) that is accessible by including git_version.h. The code functionnality does't depend on this string and therefore AutoGitVersion can be remove easely by commenting the following lines :
    - in CMakeLists.txt :
        include(../AutoGitVersion/AutoGitVersion.cmake) # Defined cmake functions : AutoGitVersion and others
        AutoGitVersion()                 # Sets up a target git_version.cpp that constains  kGitHash and GitTag as const
        set(DEPENDS_ON_GIT_VERSION git_version)
    - in python_submodule.cpp
        #include "git_version.h"
        and removing kGitInfo from the docstring.

# Building and compiling
Edit config.cmake for your machine (If you are compiling in a different envionnment than your python installation) so th  at pybind11 can be detected and used.
```bash
cmake -S . -B ./build  # Building in Linux
```
```bash
cmake -S . -B ./build -DCMAKE_TOOLCHAIN_FILE=../CMakeConfigs/mingw_toolchain.cmake # Building in Windows (Cross compiling on Cygwin with mingw)
```
```bash
cmake --build build/ # Compiles the project
```
```bash
cmake --install build/ # Copies files to their intended directory
```   
```bash
cmake --build build/ --target uninstall # uninstall 
```  
```bash
cmake --build build/ --target clean # removes targets 
```   
```bash
rm -R -f build/ # removes build directory
```  