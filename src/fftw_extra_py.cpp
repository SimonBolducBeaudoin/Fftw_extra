#include "fftw_extra_py.h"

// Numpy compatible functions
np_complex_d r2c_basic_py( np_double& in )
{
	double_1D IN        = double_1D::numpy_share(in);
	complex_d_1D out    = r2c_basic( IN ) ; 
	return out.move_py();
};

np_complex_d r2c_advanced_py( np_double& in , int l_fft , int howmany )
{
	py::buffer_info buf_in = in.request() ;
	
	if (buf_in.size != l_fft*howmany)
	{
		throw std::runtime_error(" size != l_fft*howmany ");
	}
	
	complex_d_1D out = r2c_advanced( (double*)buf_in.ptr , l_fft , howmany ); 
	return out.move_py();
};

np_double hilbert_py( np_double& in )
{
	py::buffer_info buf_in = in.request() ;
	double_1D out = hilbert( (double*)buf_in.ptr , buf_in.size ); 
	return out.move_py( buf_in.size );
};

np_complex_d analytic_py( np_double& in )
{
	py::buffer_info buf_in = in.request() ;
	complex_d_1D out = analytic( (double*)buf_in.ptr , buf_in.size ); 
	return out.move_py();
};


void init_fftw_extra(py::module &m)
{
	m.def("r2c_basic", &r2c_basic_py , "data"_a.noconvert()  ) ;
	m.def("r2c_advanced", &r2c_advanced_py , "data"_a.noconvert() , "l_fft"_a , "howmany"_a ) ;
	m.def("hilbert", &hilbert_py , "data"_a.noconvert() ) ;
	m.def("analytic", &analytic_py , "data"_a.noconvert() ) ;
}


