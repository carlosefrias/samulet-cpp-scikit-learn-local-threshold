/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sum.cpp
 *
 * Code generation for function 'sum'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "sum.h"

/* Function Definitions */
double sum(const emxArray_boolean_T *x)
{
  double y;
  int vlen;
  int k;
  vlen = x->size[0];
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= vlen; k++) {
      y += (double)x->data[k - 1];
    }
  }

  return y;
}

/* End of code generation (sum.cpp) */
