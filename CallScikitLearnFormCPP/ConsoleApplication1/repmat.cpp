/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * repmat.cpp
 *
 * Code generation for function 'repmat'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "repmat.h"
#include "Threshold_emxutil.h"

/* Function Definitions */
void repmat(const double varargin_1[2], emxArray_real_T *b)
{
  int i9;
  int loop_ub;
  int i10;
  i9 = b->size[0] * b->size[1];
  loop_ub = (int)varargin_1[0];
  b->size[0] = loop_ub;
  i10 = (int)varargin_1[1];
  b->size[1] = i10;
  emxEnsureCapacity_real_T(b, i9);
  loop_ub *= i10;
  for (i9 = 0; i9 < loop_ub; i9++) {
    b->data[i9] = 0.0;
  }
}

/* End of code generation (repmat.cpp) */
