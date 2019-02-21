/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_Threshold_api.h
 *
 * Code generation for function '_coder_Threshold_api'
 *
 */

#ifndef _CODER_THRESHOLD_API_H
#define _CODER_THRESHOLD_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Threshold_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef struct_emxArray_uint16_T
#define struct_emxArray_uint16_T

struct emxArray_uint16_T
{
  uint16_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_uint16_T*/

#ifndef typedef_emxArray_uint16_T
#define typedef_emxArray_uint16_T

typedef struct emxArray_uint16_T emxArray_uint16_T;

#endif                                 /*typedef_emxArray_uint16_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void Threshold(emxArray_uint16_T *X, real_T sensitivity, int8_T mode,
                      emxArray_real_T *T);
extern void Threshold_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1]);
extern void Threshold_atexit(void);
extern void Threshold_initialize(void);
extern void Threshold_terminate(void);
extern void Threshold_xil_terminate(void);

#endif

/* End of code generation (_coder_Threshold_api.h) */
