/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xscal.cpp
 *
 * Code generation for function 'xscal'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "xscal.h"

/* Function Definitions */
void xscal(int n, double a, emxArray_real_T *x, int ix0)
{
  int i13;
  int k;
  i13 = (ix0 + n) - 1;
  for (k = ix0; k <= i13; k++) {
    x->data[k - 1] *= a;
  }
}

/* End of code generation (xscal.cpp) */
