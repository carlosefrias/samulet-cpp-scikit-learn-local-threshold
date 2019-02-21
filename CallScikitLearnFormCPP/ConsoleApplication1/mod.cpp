/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mod.cpp
 *
 * Code generation for function 'mod'
 *
 */
#include "pch.h"
/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "mod.h"
#include "Threshold_emxutil.h"

/* Function Definitions */
void b_mod(const emxArray_real_T *x, double y, emxArray_real_T *r)
{
  int nx;
  int k;
  double b_r;
  nx = r->size[0] * r->size[1];
  r->size[0] = 1;
  r->size[1] = x->size[1];
  emxEnsureCapacity_real_T(r, nx);
  nx = x->size[1];
  for (k = 0; k < nx; k++) {
    b_r = x->data[k];
    if ((!rtIsInf(x->data[k])) && (!rtIsNaN(x->data[k])) && ((!rtIsInf(y)) &&
         (!rtIsNaN(y)))) {
      if (x->data[k] == 0.0) {
        b_r = 0.0;
      } else {
        if (y != 0.0) {
          b_r = std::fmod(x->data[k], y);
          if (b_r == 0.0) {
            b_r = 0.0;
          } else {
            if (x->data[k] < 0.0) {
              b_r += y;
            }
          }
        }
      }
    } else {
      if (y != 0.0) {
        b_r = rtNaN;
      }
    }

    r->data[k] = b_r;
  }
}

/* End of code generation (mod.cpp) */
