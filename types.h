#ifndef TYPES_H
#define TYPES_H

#include "stdint.h"

#define SBIT_BURST      16u
#define SBIT_START      24u
#define SBIT_PDN        21u
#define SBIT_EDGE       27u 
#define SBIT_DONE       31u
#define SBIT_RESULT     4u
#define SBIT_CLCKDIV    8u
#define SBIT_AD1				2u

#define NR_SAMPLES 256

typedef float real;
typedef struct{real Re; real Im;} complex;

#endif
