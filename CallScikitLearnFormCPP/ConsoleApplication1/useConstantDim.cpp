/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * useConstantDim.cpp
 *
 * Code generation for function 'useConstantDim'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "useConstantDim.h"

/* Function Definitions */
void useConstantDim(emxArray_real_T *varargin_2, int varargin_3)
{
  int i17;
  int k;
  int i18;
  int subsa_tmp_idx_1;
  int b_k;
  int subsa_tmp_idx_0;
  if (1 == varargin_3) {
    if ((varargin_2->size[0] != 0) && (varargin_2->size[1] != 0)) {
      i17 = varargin_2->size[1];
      for (k = 0; k < i17; k++) {
        i18 = varargin_2->size[0];
        if (0 <= i18 - 2) {
          subsa_tmp_idx_1 = k + 1;
        }

        for (b_k = 0; b_k <= i18 - 2; b_k++) {
          subsa_tmp_idx_0 = 1 + b_k;
          varargin_2->data[subsa_tmp_idx_0 + varargin_2->size[0] *
            (subsa_tmp_idx_1 - 1)] += varargin_2->data[(subsa_tmp_idx_0 +
            varargin_2->size[0] * (subsa_tmp_idx_1 - 1)) - 1];
        }
      }
    }
  } else {
    if ((varargin_2->size[0] != 0) && (varargin_2->size[1] != 0)) {
      i17 = varargin_2->size[1];
      for (k = 0; k <= i17 - 2; k++) {
        i18 = varargin_2->size[0];
        if (0 <= i18 - 1) {
          subsa_tmp_idx_1 = k + 1;
        }

        for (b_k = 0; b_k < i18; b_k++) {
          subsa_tmp_idx_0 = 1 + b_k;
          varargin_2->data[(subsa_tmp_idx_0 + varargin_2->size[0] *
                            subsa_tmp_idx_1) - 1] += varargin_2->data
            [(subsa_tmp_idx_0 + varargin_2->size[0] * (subsa_tmp_idx_1 - 1)) - 1];
        }
      }
    }
  }
}

/* End of code generation (useConstantDim.cpp) */
