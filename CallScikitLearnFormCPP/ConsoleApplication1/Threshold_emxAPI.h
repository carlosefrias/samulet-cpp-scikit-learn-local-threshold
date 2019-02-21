/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Threshold_emxAPI.h
 *
 * Code generation for function 'Threshold_emxAPI'
 *
 */

#ifndef THRESHOLD_EMXAPI_H
#define THRESHOLD_EMXAPI_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Threshold_types.h"

/* Function Declarations */
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_uint16_T *emxCreateND_uint16_T(int numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, int *size);
extern emxArray_uint16_T *emxCreateWrapperND_uint16_T(unsigned short *data, int
  numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_uint16_T *emxCreateWrapper_uint16_T(unsigned short *data, int
  rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern emxArray_uint16_T *emxCreate_uint16_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
extern void emxDestroyArray_uint16_T(emxArray_uint16_T *emxArray);
extern void emxInitArray_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInitArray_uint16_T(emxArray_uint16_T **pEmxArray, int
  numDimensions);

#endif

/* End of code generation (Threshold_emxAPI.h) */
