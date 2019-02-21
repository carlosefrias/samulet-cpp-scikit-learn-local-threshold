/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * svd.cpp
 *
 * Code generation for function 'svd'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "svd.h"
#include "Threshold_emxutil.h"
#include "svd1.h"

/* Function Definitions */
void svd(const emxArray_real_T *A, emxArray_real_T *U, emxArray_real_T *S,
         emxArray_real_T *V)
{
  int nx;
  boolean_T p;
  int k;
  emxArray_real_T *s;
  double x;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  emxArray_real_T *r0;
  int i5;
  emxArray_real_T *U1;
  emxArray_real_T *V1;
  nx = A->size[0] * A->size[1];
  p = true;
  for (k = 0; k < nx; k++) {
    if (p) {
      x = A->data[k];
      if ((!rtIsInf(x)) && (!rtIsNaN(x))) {
        p = true;
      } else {
        p = false;
      }
    } else {
      p = false;
    }
  }

  emxInit_real_T(&s, 1);
  if (p) {
    b_svd(A, U, s, V);
  } else {
    unnamed_idx_0 = (unsigned int)A->size[0];
    unnamed_idx_1 = (unsigned int)A->size[1];
    emxInit_real_T(&r0, 2);
    i5 = r0->size[0] * r0->size[1];
    r0->size[0] = (int)unnamed_idx_0;
    r0->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity_real_T(r0, i5);
    nx = (int)unnamed_idx_0 * (int)unnamed_idx_1;
    for (i5 = 0; i5 < nx; i5++) {
      r0->data[i5] = 0.0;
    }

    emxInit_real_T(&U1, 2);
    emxInit_real_T(&V1, 2);
    b_svd(r0, U1, s, V1);
    i5 = U->size[0] * U->size[1];
    U->size[0] = U1->size[0];
    U->size[1] = U1->size[1];
    emxEnsureCapacity_real_T(U, i5);
    nx = U1->size[0] * U1->size[1];
    emxFree_real_T(&r0);
    emxFree_real_T(&U1);
    for (i5 = 0; i5 < nx; i5++) {
      U->data[i5] = rtNaN;
    }

    nx = s->size[0];
    i5 = s->size[0];
    s->size[0] = nx;
    emxEnsureCapacity_real_T(s, i5);
    for (i5 = 0; i5 < nx; i5++) {
      s->data[i5] = rtNaN;
    }

    i5 = V->size[0] * V->size[1];
    V->size[0] = V1->size[0];
    V->size[1] = V1->size[1];
    emxEnsureCapacity_real_T(V, i5);
    nx = V1->size[0] * V1->size[1];
    emxFree_real_T(&V1);
    for (i5 = 0; i5 < nx; i5++) {
      V->data[i5] = rtNaN;
    }
  }

  i5 = S->size[0] * S->size[1];
  S->size[0] = U->size[1];
  S->size[1] = V->size[1];
  emxEnsureCapacity_real_T(S, i5);
  nx = U->size[1] * V->size[1];
  for (i5 = 0; i5 < nx; i5++) {
    S->data[i5] = 0.0;
  }

  i5 = s->size[0] - 1;
  for (k = 0; k <= i5; k++) {
    S->data[k + S->size[0] * k] = s->data[k];
  }

  emxFree_real_T(&s);
}

/* End of code generation (svd.cpp) */
