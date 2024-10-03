#pragma once

#include <Multi_array.h>
#include <fftw3.h>

typedef unsigned int uint;
typedef std::complex<double> complex_d;

typedef Multi_array<double, 1, uint> double_1D;
typedef Multi_array<complex_d, 1, uint> complex_d_1D;

/*
        Functions
*/

/*
        out of place r2c fft

        MEANT FOR BEANCHMARKS
*/

// WARNING !! PLAN CREATION ERASES DATA !
// THEREFORE ON THE FIRST USAGE THIS FUNCTION WILL ERASE INPUT AND RETURN ZEROS
complex_d_1D r2c_basic(double *in, int l_fft);
complex_d_1D r2c_basic(const double_1D &in);

/*
        FFTW's advanced interface wrapper for easy python benchmarking
        See :
   http://www.fftw.org/fftw3_doc/Advanced-Real_002ddata-DFTs.html#Advanced-Real_002ddata-DFTs
*/
complex_d_1D r2c_advanced(double *in, int l_fft, int howmany = 1);
complex_d_1D r2c_advanced(const double_1D &in, int howmany = 1);

/* Out of place hilbert transform */
/*
        simple implementation of out of place Hilbert transform
        See :
   https://stackoverflow.com/questions/46241823/fftw-computing-analytic-signal-from-r2c-real-to-complex-data
        Warnign : Output allocated array is slightly longer(+2 double). This
   padding is only for efficiency and doesn't carry meaning.
*/
double_1D hilbert(double *in, int l_fft);
double_1D hilbert(const double_1D &in);

/* Analitic signal transform */
/*
        simple implementation of out of place anaytic signal calculation from a
   real input See :
   https://stackoverflow.com/questions/46241823/fftw-computing-analytic-signal-from-r2c-real-to-complex-data
*/
complex_d_1D analytic(double *in, int l_fft);
complex_d_1D analytic(const double_1D &in);
