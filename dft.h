#ifndef DFT_H
#define DFT_H

#include <stdio.h>
#include <math.h>

#include "types.h"

void fft( complex *v, int n, complex *tmp );
void ifft( complex *v, int n, complex *tmp );

void FFT(unsigned int logN, double *real, double *im);

#endif
