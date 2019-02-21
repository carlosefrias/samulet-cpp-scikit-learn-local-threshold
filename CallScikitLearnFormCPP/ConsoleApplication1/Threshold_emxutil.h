/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Threshold_emxutil.h
 *
 * Code generation for function 'Threshold_emxutil'
 *
 */

#ifndef THRESHOLD_EMXUTIL_H
#define THRESHOLD_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Threshold_types.h"

/* Function Declarations */
extern void emxEnsureCapacity_boolean_T(emxArray_boolean_T *emxArray, int
  oldNumel);
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_int8_T(emxArray_int8_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxEnsureCapacity_uint32_T(emxArray_uint32_T *emxArray, int oldNumel);
extern void emxFree_boolean_T(emxArray_boolean_T **pEmxArray);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxFree_int8_T(emxArray_int8_T **pEmxArray);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxFree_uint16_T(emxArray_uint16_T **pEmxArray);
extern void emxFree_uint32_T(emxArray_uint32_T **pEmxArray);
extern void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);
extern void emxInit_int8_T(emxArray_int8_T **pEmxArray, int numDimensions);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);
extern void emxInit_uint16_T(emxArray_uint16_T **pEmxArray, int numDimensions);
extern void emxInit_uint32_T(emxArray_uint32_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (Threshold_emxutil.h) */
