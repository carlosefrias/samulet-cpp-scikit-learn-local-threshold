/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ordfilt2.cpp
 *
 * Code generation for function 'ordfilt2'
 *
 */
#include "pch.h"
/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "ordfilt2.h"
#include "Threshold_emxutil.h"
#include "padarray.h"
#include "abs.h"
#include "sum.h"
#include "Threshold_rtwutil.h"
#include "libmwordfilt2.h"

/* Function Declarations */
static int div_s32(int numerator, int denominator);

/* Function Definitions */
static int div_s32(int numerator, int denominator)
{
  int quotient;
  unsigned int b_numerator;
  unsigned int b_denominator;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      b_numerator = ~(unsigned int)numerator + 1U;
    } else {
      b_numerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      b_denominator = ~(unsigned int)denominator + 1U;
    } else {
      b_denominator = (unsigned int)denominator;
    }

    tempAbsQuotient = b_numerator / b_denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

void ordfilt2(emxArray_real_T *varargin_1, double varargin_2, const
              emxArray_real_T *varargin_3)
{
  emxArray_boolean_T *domain;
  int i19;
  int n;
  double domainSize[2];
  int center_idx_0;
  int center_idx_1;
  emxArray_real_T *cols;
  int idx;
  emxArray_boolean_T b_domain;
  int c_domain[1];
  double numElems;
  emxArray_real_T *rows;
  unsigned int b_index;
  double startIdx[2];
  int vk;
  int i20;
  emxArray_real_T *b_varargin_1;
  boolean_T exitg1;
  double ex;
  double padSize[2];
  emxArray_real_T *Apad;
  emxArray_int32_T *indices;
  emxInit_boolean_T(&domain, 2);
  i19 = domain->size[0] * domain->size[1];
  domain->size[0] = varargin_3->size[0];
  domain->size[1] = varargin_3->size[1];
  emxEnsureCapacity_boolean_T(domain, i19);
  n = varargin_3->size[0] * varargin_3->size[1];
  for (i19 = 0; i19 < n; i19++) {
    domain->data[i19] = (varargin_3->data[i19] != 0.0);
  }

  domainSize[0] = domain->size[0];
  domainSize[1] = domain->size[1];
  center_idx_0 = (int)std::floor((domainSize[0] + 1.0) / 2.0);
  center_idx_1 = (int)std::floor((domainSize[1] + 1.0) / 2.0);
  emxInit_real_T(&cols, 1);
  idx = domain->size[0] * domain->size[1];
  b_domain = *domain;
  c_domain[0] = idx;
  b_domain.size = &c_domain[0];
  b_domain.numDimensions = 1;
  numElems = sum(&b_domain);
  i19 = cols->size[0];
  n = (int)numElems;
  cols->size[0] = n;
  emxEnsureCapacity_real_T(cols, i19);
  for (i19 = 0; i19 < n; i19++) {
    cols->data[i19] = 0.0;
  }

  emxInit_real_T(&rows, 1);
  i19 = rows->size[0];
  rows->size[0] = n;
  emxEnsureCapacity_real_T(rows, i19);
  for (i19 = 0; i19 < n; i19++) {
    rows->data[i19] = 0.0;
  }

  b_index = 1U;
  i19 = domain->size[0] * domain->size[1];
  for (idx = 0; idx < i19; idx++) {
    startIdx[0] = domain->size[0];
    n = (int)(unsigned int)startIdx[0];
    vk = div_s32(idx, n);
    i20 = (int)b_index - 1;
    rows->data[i20] = (idx - vk * n) + 1;
    cols->data[i20] = vk + 1;
    b_index++;
  }

  emxFree_boolean_T(&domain);
  i19 = rows->size[0];
  emxEnsureCapacity_real_T(rows, i19);
  n = rows->size[0];
  for (i19 = 0; i19 < n; i19++) {
    rows->data[i19] -= (double)center_idx_0;
  }

  i19 = cols->size[0];
  emxEnsureCapacity_real_T(cols, i19);
  n = cols->size[0];
  for (i19 = 0; i19 < n; i19++) {
    cols->data[i19] -= (double)center_idx_1;
  }

  emxInit_real_T(&b_varargin_1, 1);
  b_abs(rows, b_varargin_1);
  n = b_varargin_1->size[0];
  if (b_varargin_1->size[0] <= 2) {
    if (b_varargin_1->size[0] == 1) {
      numElems = b_varargin_1->data[0];
    } else if ((b_varargin_1->data[0] < b_varargin_1->data[1]) || (rtIsNaN
                (b_varargin_1->data[0]) && (!rtIsNaN(b_varargin_1->data[1])))) {
      numElems = b_varargin_1->data[1];
    } else {
      numElems = b_varargin_1->data[0];
    }
  } else {
    if (!rtIsNaN(b_varargin_1->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      vk = 2;
      exitg1 = false;
      while ((!exitg1) && (vk <= b_varargin_1->size[0])) {
        if (!rtIsNaN(b_varargin_1->data[vk - 1])) {
          idx = vk;
          exitg1 = true;
        } else {
          vk++;
        }
      }
    }

    if (idx == 0) {
      numElems = b_varargin_1->data[0];
    } else {
      numElems = b_varargin_1->data[idx - 1];
      i19 = idx + 1;
      for (vk = i19; vk <= n; vk++) {
        if (numElems < b_varargin_1->data[vk - 1]) {
          numElems = b_varargin_1->data[vk - 1];
        }
      }
    }
  }

  b_abs(cols, b_varargin_1);
  n = b_varargin_1->size[0];
  if (b_varargin_1->size[0] <= 2) {
    if (b_varargin_1->size[0] == 1) {
      ex = b_varargin_1->data[0];
    } else if ((b_varargin_1->data[0] < b_varargin_1->data[1]) || (rtIsNaN
                (b_varargin_1->data[0]) && (!rtIsNaN(b_varargin_1->data[1])))) {
      ex = b_varargin_1->data[1];
    } else {
      ex = b_varargin_1->data[0];
    }
  } else {
    if (!rtIsNaN(b_varargin_1->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      vk = 2;
      exitg1 = false;
      while ((!exitg1) && (vk <= b_varargin_1->size[0])) {
        if (!rtIsNaN(b_varargin_1->data[vk - 1])) {
          idx = vk;
          exitg1 = true;
        } else {
          vk++;
        }
      }
    }

    if (idx == 0) {
      ex = b_varargin_1->data[0];
    } else {
      ex = b_varargin_1->data[idx - 1];
      i19 = idx + 1;
      for (vk = i19; vk <= n; vk++) {
        if (ex < b_varargin_1->data[vk - 1]) {
          ex = b_varargin_1->data[vk - 1];
        }
      }
    }
  }

  emxFree_real_T(&b_varargin_1);
  if ((numElems > ex) || rtIsNaN(ex)) {
  } else {
    numElems = ex;
  }

  padSize[0] = numElems;
  padSize[1] = numElems;
  emxInit_real_T(&Apad, 2);
  b_padarray(varargin_1, padSize, Apad);
  if ((varargin_1->size[0] != 0) && (varargin_1->size[1] != 0)) {
    emxInit_int32_T(&indices, 1);
    idx = Apad->size[0];
    i19 = indices->size[0];
    indices->size[0] = cols->size[0];
    emxEnsureCapacity_int32_T(indices, i19);
    n = cols->size[0];
    for (i19 = 0; i19 < n; i19++) {
      ex = rt_roundd_snf(cols->data[i19] * (double)idx + rows->data[i19]);
      if (ex < 2.147483648E+9) {
        if (ex >= -2.147483648E+9) {
          i20 = (int)ex;
        } else {
          i20 = MIN_int32_T;
        }
      } else if (ex >= 2.147483648E+9) {
        i20 = MAX_int32_T;
      } else {
        i20 = 0;
      }

      indices->data[i19] = i20;
    }

    startIdx[0] = numElems;
    startIdx[1] = numElems;
    idx = varargin_1->size[0];
    n = varargin_1->size[1];
    i19 = varargin_1->size[0] * varargin_1->size[1];
    varargin_1->size[0] = idx;
    varargin_1->size[1] = n;
    emxEnsureCapacity_real_T(varargin_1, i19);
    padSize[0] = varargin_1->size[0];
    padSize[1] = varargin_1->size[1];
    ordfilt2_real64(&Apad->data[0], (double)Apad->size[0], startIdx,
                    &indices->data[0], (double)indices->size[0], domainSize,
                    varargin_2 - 1.0, &varargin_1->data[0], padSize, true);
    emxFree_int32_T(&indices);
  }

  emxFree_real_T(&Apad);
  emxFree_real_T(&cols);
  emxFree_real_T(&rows);
}

/* End of code generation (ordfilt2.cpp) */
