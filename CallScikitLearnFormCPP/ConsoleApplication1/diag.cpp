/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * diag.cpp
 *
 * Code generation for function 'diag'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "diag.h"
#include "Threshold_emxutil.h"

/* Function Definitions */
void diag(const emxArray_real_T *v, emxArray_real_T *d)
{
  int u0;
  int i6;
  int u1;
  if ((v->size[0] == 1) && (v->size[1] == 1)) {
    i6 = d->size[0];
    d->size[0] = 1;
    emxEnsureCapacity_real_T(d, i6);
    d->data[0] = v->data[0];
  } else {
    u0 = v->size[0];
    u1 = v->size[1];
    if (u0 < u1) {
      u1 = u0;
    }

    i6 = d->size[0];
    d->size[0] = u1;
    emxEnsureCapacity_real_T(d, i6);
    i6 = u1 - 1;
    for (u0 = 0; u0 <= i6; u0++) {
      d->data[u0] = v->data[u0 + v->size[0] * u0];
    }
  }
}

/* End of code generation (diag.cpp) */
