/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdotc.cpp
 *
 * Code generation for function 'xdotc'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "xdotc.h"

/* Function Definitions */
double xdotc(int n, const emxArray_real_T *x, int ix0, const emxArray_real_T *y,
             int iy0)
{
  double d;
  int ix;
  int iy;
  int k;
  d = 0.0;
  if (n >= 1) {
    ix = ix0;
    iy = iy0;
    for (k = 0; k < n; k++) {
      d += x->data[ix - 1] * y->data[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/* End of code generation (xdotc.cpp) */
