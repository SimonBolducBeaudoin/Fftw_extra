#include "python_submodule.h"
#include "git_version.h"

// See Pybind11 FAQ «How can I reduce the build time ?» :
// https://pybind11.readthedocs.io/en/stable/faq.html#how-can-i-reduce-the-build-time

//Python Binding and Time_Quad class instances.
PYBIND11_MODULE(fftw_extra, m)
{
    m.doc() = "Extra function related to fftw library.\n"\
    "Git Info : \n "\
    + std::string(kGitInfo)\
    +"\n";   
	init_fftw_extra(m);
}

