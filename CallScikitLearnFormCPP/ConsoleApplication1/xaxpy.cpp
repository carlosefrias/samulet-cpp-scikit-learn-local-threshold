/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xaxpy.cpp
 *
 * Code generation for function 'xaxpy'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "xaxpy.h"

/* Function Definitions */
void b_xaxpy(int n, double a, const emxArray_real_T *x, int ix0, emxArray_real_T
             *y, int iy0)
{
  int ix;
  int iy;
  int i15;
  int k;
  if ((n < 1) || (a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    i15 = n - 1;
    for (k = 0; k <= i15; k++) {
      y->data[iy] += a * x->data[ix];
      ix++;
      iy++;
    }
  }
}

void xaxpy(int n, double a, int ix0, emxArray_real_T *y, int iy0)
{
  int ix;
  int iy;
  int i14;
  int k;
  if ((n < 1) || (a == 0.0)) {
  } else {
    ix = ix0 - 1;
    iy = iy0 - 1;
    i14 = n - 1;
    for (k = 0; k <= i14; k++) {
      y->data[iy] += a * y->data[ix];
      ix++;
      iy++;
    }
  }
}

/* End of code generation (xaxpy.cpp) */
