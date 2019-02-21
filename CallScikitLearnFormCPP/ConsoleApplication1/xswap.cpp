/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xswap.cpp
 *
 * Code generation for function 'xswap'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "xswap.h"

/* Function Definitions */
void xswap(int n, emxArray_real_T *x, int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  double temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < n; k++) {
    temp = x->data[ix];
    x->data[ix] = x->data[iy];
    x->data[iy] = temp;
    ix++;
    iy++;
  }
}

/* End of code generation (xswap.cpp) */
