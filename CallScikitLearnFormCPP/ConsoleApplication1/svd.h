/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * svd.h
 *
 * Code generation for function 'svd'
 *
 */

#ifndef SVD_H
#define SVD_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Threshold_types.h"

/* Function Declarations */
extern void svd(const emxArray_real_T *A, emxArray_real_T *U, emxArray_real_T *S,
                emxArray_real_T *V);

#endif

/* End of code generation (svd.h) */
