#include "../includes/fftw_extra.h"

complex_d_1D r2c_basic(	double* in , int l_fft )
{ 
	// Not normalized
	complex_d_1D out( l_fft/2 + 1 , fftw_malloc , fftw_free ) ;
	fftw_import_wisdom_from_filename("FFTW_Wisdom.dat");
	fftw_plan plan 	= fftw_plan_dft_r2c_1d( l_fft , in , reinterpret_cast<fftw_complex*>( &out[0] ) , FFTW_EXHAUSTIVE ); // Out of place
	fftw_export_wisdom_to_filename("FFTW_Wisdom.dat");	
	fftw_execute( plan ); // Out of place
	fftw_destroy_plan( plan );
	return out ;
};

complex_d_1D r2c_basic(	const double_1D& in )
{
	return r2c_basic( in.get_ptr() , in.get_n_i() );
};

complex_d_1D r2c_advanced( double* in , int l_fft , int howmany )
{
	// Not normalized
	complex_d_1D out( howmany*(l_fft/2 + 1) , fftw_malloc , fftw_free ) ;
	fftw_import_wisdom_from_filename("FFTW_Wisdom.dat");
	int n[] = {l_fft} ;
	fftw_plan plan = 
		fftw_plan_many_dft_r2c // In place ifft with strides 
		( 
			1 , // rank
			n , //  list of dimensions 
			howmany , // howmany (to do many ffts on the same core)
			in , // input
			NULL , // inembed
			1 , // istride
			0 , // idist
			reinterpret_cast<fftw_complex*>( &out[0] ) , // output pointer
			NULL , //  onembed
			1 , // ostride
			0 , // odist
			FFTW_EXHAUSTIVE
		);
	fftw_export_wisdom_to_filename("FFTW_Wisdom.dat");	
	fftw_execute( plan ); // Out of place	
	fftw_destroy_plan(plan);
	return out ;
};

complex_d_1D r2c_advanced( const double_1D& in , int l_fft, int howmany )
{
	return r2c_advanced( in.get_ptr() , l_fft , howmany ) ;
};

double_1D hilbert( double* in , int l_fft  )
{
	const complex_d mI (0,-1.0/l_fft); // Minus Imaginary number with normalisation factor
	double_1D out( l_fft + 2 , fftw_malloc , fftw_free ) ;
	complex_d_1D out_complex( (complex_d*)out.get_ptr() , l_fft/2 + 1 ); // Shared memory but different cast-type
	
	fftw_import_wisdom_from_filename("FFTW_Wisdom.dat");
	fftw_plan plan_foward 	= fftw_plan_dft_r2c_1d( l_fft , in , reinterpret_cast<fftw_complex*>( &out_complex[0] ) , FFTW_EXHAUSTIVE ); // Out of place
	fftw_plan plan_backward = fftw_plan_dft_c2r_1d( l_fft , reinterpret_cast<fftw_complex*>(&out_complex[0]) , &out[0] 	, FFTW_EXHAUSTIVE ); // In place
	fftw_export_wisdom_to_filename("FFTW_Wisdom.dat");	
	
	fftw_execute( plan_foward ); // Out of place
	for( int i=0; i < l_fft/2+1 ; i++ )
	{
		out_complex[i] *= mI ;
	}
	fftw_execute( plan_backward ); // In place
	
	return out ;
};

double_1D hilbert( const double_1D& in )
{
	return hilbert( in.get_ptr() , in.get_n_i() ) ;
};

complex_d_1D analytic( double* in , int l_fft )
{	
	const complex_d mI (0,-1.0/l_fft); // Minus Imaginary number with normalisation factor
	complex_d_1D tmp( l_fft/2 + 1  , fftw_malloc , fftw_free ) ; // Real part is the in array imaginary part is Hilbert(in).
	complex_d_1D out( l_fft  , fftw_malloc , fftw_free ) ; // Real part is the in array imaginary part is Hilbert(in).
	
	double* real_ptr = (double*)out.get_ptr() ;
	double* imag_ptr = (double*)out.get_ptr() + 1 ;
	
	fftw_import_wisdom_from_filename("FFTW_Wisdom.dat");
	fftw_plan plan_foward = fftw_plan_dft_r2c_1d( l_fft , in , reinterpret_cast<fftw_complex*>( &tmp[0] ) , FFTW_EXHAUSTIVE ); // Out of place
	
	int rank = 1 ;
	const int n[] = {l_fft} ; //  list of dimensions 
	int howmany = 1 ; 
	// in
	const int* inembed = NULL ;
	int istride = 1 ;
	int idist = 0 ;
	//
	const int* onembed = NULL ; 
	const int ostride = 2 ;
	const int odist = 0 ; 
	unsigned flags = FFTW_EXHAUSTIVE ;
	fftw_plan plan_backward = 	fftw_plan_many_dft_c2r
								(	
									rank , n , howmany , 
									reinterpret_cast<fftw_complex*>(&tmp[0]) , inembed , istride , idist , 
									imag_ptr , onembed , ostride , odist , 
									flags
								);
		
	fftw_export_wisdom_to_filename("FFTW_Wisdom.dat");	
	fftw_execute( plan_foward ); // out of place r2c
	for( int i=0; i < l_fft/2+1 ; i++ ) // rotation for hilbert transform
	{
		tmp[i] *= mI ;	
	}
	fftw_execute( plan_backward ); // in-place transform with stride of 2*(sizeof(double)) in outputs
	/* Copy operation for the real part */
	for( int i=0; i < l_fft ; i++ )
	{
		*( real_ptr + 2*i ) = in[i] ; // Multiplication is there so that Real and imaginary parts have the same normalization
	}
	
	return out ;
};

complex_d_1D analytic( const double_1D& in )
{
	return analytic( in.get_ptr() , in.get_n_i() ) ;
};


















