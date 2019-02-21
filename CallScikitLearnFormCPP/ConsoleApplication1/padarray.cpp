/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * padarray.cpp
 *
 * Code generation for function 'padarray'
 *
 */
#include "pch.h"
/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "padarray.h"
#include "repmat.h"
#include "Threshold_emxutil.h"
#include "mod.h"
#include "Threshold_rtwutil.h"

/* Function Definitions */
void b_padarray(const emxArray_real_T *varargin_1, const double varargin_2[2],
                emxArray_real_T *b)
{
  double sizeA_idx_0;
  double sizeA_idx_1;
  double varargin_1_idx_0;
  double sizeA[2];
  double ndbl;
  emxArray_int32_T *idxA;
  emxArray_real_T *y;
  int i11;
  int nm1d2;
  emxArray_real_T *b_y;
  emxArray_uint32_T *dimNums;
  unsigned int u0;
  double apnd;
  double cdiff;
  emxArray_uint32_T *idxDir;
  double b_u0;
  double u1;
  int n;
  emxArray_int32_T *r2;
  int k;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    sizeA_idx_0 = (double)varargin_1->size[0] + 2.0 * varargin_2[0];
    sizeA_idx_1 = (double)varargin_1->size[1] + 2.0 * varargin_2[1];
    sizeA[0] = sizeA_idx_0;
    sizeA[1] = sizeA_idx_1;
    repmat(sizeA, b);
  } else {
    sizeA_idx_0 = varargin_1->size[0];
    sizeA_idx_1 = varargin_1->size[1];
    varargin_1_idx_0 = 2.0 * varargin_2[0] + (double)(unsigned int)sizeA_idx_0;
    ndbl = 2.0 * varargin_2[1] + (double)(unsigned int)sizeA_idx_1;
    if ((varargin_1_idx_0 < ndbl) || (rtIsNaN(varargin_1_idx_0) && (!rtIsNaN
          (ndbl)))) {
      varargin_1_idx_0 = ndbl;
    }

    emxInit_int32_T(&idxA, 2);
    emxInit_real_T(&y, 2);
    i11 = idxA->size[0] * idxA->size[1];
    idxA->size[0] = (int)varargin_1_idx_0;
    idxA->size[1] = 2;
    emxEnsureCapacity_int32_T(idxA, i11);
    i11 = y->size[0] * y->size[1];
    y->size[0] = 1;
    nm1d2 = (int)(unsigned int)sizeA_idx_0 - 1;
    y->size[1] = nm1d2 + 1;
    emxEnsureCapacity_real_T(y, i11);
    for (i11 = 0; i11 <= nm1d2; i11++) {
      y->data[i11] = 1.0 + (double)i11;
    }

    emxInit_real_T(&b_y, 2);
    i11 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    nm1d2 = (int)(unsigned int)sizeA_idx_0 - 1;
    b_y->size[1] = nm1d2 + 1;
    emxEnsureCapacity_real_T(b_y, i11);
    for (i11 = 0; i11 <= nm1d2; i11++) {
      b_y->data[i11] = (double)(unsigned int)sizeA_idx_0 - (double)i11;
    }

    emxInit_uint32_T(&dimNums, 2);
    i11 = dimNums->size[0] * dimNums->size[1];
    dimNums->size[0] = 1;
    dimNums->size[1] = y->size[1] + b_y->size[1];
    emxEnsureCapacity_uint32_T(dimNums, i11);
    nm1d2 = y->size[1];
    for (i11 = 0; i11 < nm1d2; i11++) {
      varargin_1_idx_0 = rt_roundd_snf(y->data[i11]);
      if (varargin_1_idx_0 < 4.294967296E+9) {
        if (varargin_1_idx_0 >= 0.0) {
          u0 = (unsigned int)varargin_1_idx_0;
        } else {
          u0 = 0U;
        }
      } else if (varargin_1_idx_0 >= 4.294967296E+9) {
        u0 = MAX_uint32_T;
      } else {
        u0 = 0U;
      }

      dimNums->data[i11] = u0;
    }

    nm1d2 = b_y->size[1];
    for (i11 = 0; i11 < nm1d2; i11++) {
      varargin_1_idx_0 = rt_roundd_snf(b_y->data[i11]);
      if (varargin_1_idx_0 < 4.294967296E+9) {
        if (varargin_1_idx_0 >= 0.0) {
          u0 = (unsigned int)varargin_1_idx_0;
        } else {
          u0 = 0U;
        }
      } else if (varargin_1_idx_0 >= 4.294967296E+9) {
        u0 = MAX_uint32_T;
      } else {
        u0 = 0U;
      }

      dimNums->data[i11 + y->size[1]] = u0;
    }

    varargin_1_idx_0 = ((double)(unsigned int)sizeA_idx_0 + varargin_2[0]) - 1.0;
    if (rtIsNaN(-varargin_2[0]) || rtIsNaN(varargin_1_idx_0)) {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i11);
      y->data[0] = rtNaN;
    } else if (varargin_1_idx_0 < -varargin_2[0]) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if ((rtIsInf(-varargin_2[0]) || rtIsInf(varargin_1_idx_0)) &&
               (-varargin_2[0] == varargin_1_idx_0)) {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i11);
      y->data[0] = rtNaN;
    } else if (std::floor(-varargin_2[0]) == -varargin_2[0]) {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 1;
      nm1d2 = (int)std::floor(varargin_1_idx_0 - (-varargin_2[0]));
      y->size[1] = nm1d2 + 1;
      emxEnsureCapacity_real_T(y, i11);
      for (i11 = 0; i11 <= nm1d2; i11++) {
        y->data[i11] = -varargin_2[0] + (double)i11;
      }
    } else {
      ndbl = std::floor((varargin_1_idx_0 - (-varargin_2[0])) + 0.5);
      apnd = -varargin_2[0] + ndbl;
      cdiff = apnd - varargin_1_idx_0;
      b_u0 = std::abs(-varargin_2[0]);
      u1 = std::abs(varargin_1_idx_0);
      if ((b_u0 > u1) || rtIsNaN(u1)) {
        u1 = b_u0;
      }

      if (std::abs(cdiff) < 4.4408920985006262E-16 * u1) {
        ndbl++;
        apnd = varargin_1_idx_0;
      } else if (cdiff > 0.0) {
        apnd = -varargin_2[0] + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i11 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = n;
      emxEnsureCapacity_real_T(y, i11);
      if (n > 0) {
        y->data[0] = -varargin_2[0];
        if (n > 1) {
          y->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 0; k <= nm1d2 - 2; k++) {
            y->data[1 + k] = -varargin_2[0] + (1.0 + (double)k);
            y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
          }

          if (nm1d2 << 1 == n - 1) {
            y->data[nm1d2] = (-varargin_2[0] + apnd) / 2.0;
          } else {
            y->data[nm1d2] = -varargin_2[0] + (double)nm1d2;
            y->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    emxInit_uint32_T(&idxDir, 2);
    varargin_1_idx_0 = 2.0 * (double)(unsigned int)sizeA_idx_0;
    b_mod(y, varargin_1_idx_0, b_y);
    i11 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = b_y->size[1];
    emxEnsureCapacity_uint32_T(idxDir, i11);
    nm1d2 = b_y->size[0] * b_y->size[1];
    for (i11 = 0; i11 < nm1d2; i11++) {
      idxDir->data[i11] = dimNums->data[(int)(b_y->data[i11] + 1.0) - 1];
    }

    b_mod(y, varargin_1_idx_0, b_y);
    if (1 > b_y->size[1]) {
      nm1d2 = 0;
    } else {
      b_mod(y, varargin_1_idx_0, b_y);
      nm1d2 = b_y->size[1];
    }

    emxInit_int32_T(&r2, 1);
    i11 = r2->size[0];
    r2->size[0] = nm1d2;
    emxEnsureCapacity_int32_T(r2, i11);
    for (i11 = 0; i11 < nm1d2; i11++) {
      r2->data[i11] = i11;
    }

    nm1d2 = r2->size[0];
    for (i11 = 0; i11 < nm1d2; i11++) {
      idxA->data[r2->data[i11]] = (int)idxDir->data[i11];
    }

    i11 = y->size[0] * y->size[1];
    y->size[0] = 1;
    nm1d2 = (int)(unsigned int)sizeA_idx_1 - 1;
    y->size[1] = nm1d2 + 1;
    emxEnsureCapacity_real_T(y, i11);
    for (i11 = 0; i11 <= nm1d2; i11++) {
      y->data[i11] = 1.0 + (double)i11;
    }

    i11 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    nm1d2 = (int)(unsigned int)sizeA_idx_1 - 1;
    b_y->size[1] = nm1d2 + 1;
    emxEnsureCapacity_real_T(b_y, i11);
    for (i11 = 0; i11 <= nm1d2; i11++) {
      b_y->data[i11] = (double)(unsigned int)sizeA_idx_1 - (double)i11;
    }

    i11 = dimNums->size[0] * dimNums->size[1];
    dimNums->size[0] = 1;
    dimNums->size[1] = y->size[1] + b_y->size[1];
    emxEnsureCapacity_uint32_T(dimNums, i11);
    nm1d2 = y->size[1];
    for (i11 = 0; i11 < nm1d2; i11++) {
      varargin_1_idx_0 = rt_roundd_snf(y->data[i11]);
      if (varargin_1_idx_0 < 4.294967296E+9) {
        if (varargin_1_idx_0 >= 0.0) {
          u0 = (unsigned int)varargin_1_idx_0;
        } else {
          u0 = 0U;
        }
      } else if (varargin_1_idx_0 >= 4.294967296E+9) {
        u0 = MAX_uint32_T;
      } else {
        u0 = 0U;
      }

      dimNums->data[i11] = u0;
    }

    nm1d2 = b_y->size[1];
    for (i11 = 0; i11 < nm1d2; i11++) {
      varargin_1_idx_0 = rt_roundd_snf(b_y->data[i11]);
      if (varargin_1_idx_0 < 4.294967296E+9) {
        if (varargin_1_idx_0 >= 0.0) {
          u0 = (unsigned int)varargin_1_idx_0;
        } else {
          u0 = 0U;
        }
      } else if (varargin_1_idx_0 >= 4.294967296E+9) {
        u0 = MAX_uint32_T;
      } else {
        u0 = 0U;
      }

      dimNums->data[i11 + y->size[1]] = u0;
    }

    varargin_1_idx_0 = ((double)(unsigned int)sizeA_idx_1 + varargin_2[1]) - 1.0;
    if (rtIsNaN(-varargin_2[1]) || rtIsNaN(varargin_1_idx_0)) {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i11);
      y->data[0] = rtNaN;
    } else if (varargin_1_idx_0 < -varargin_2[1]) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if ((rtIsInf(-varargin_2[1]) || rtIsInf(varargin_1_idx_0)) &&
               (-varargin_2[1] == varargin_1_idx_0)) {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i11);
      y->data[0] = rtNaN;
    } else if (std::floor(-varargin_2[1]) == -varargin_2[1]) {
      i11 = y->size[0] * y->size[1];
      y->size[0] = 1;
      nm1d2 = (int)std::floor(varargin_1_idx_0 - (-varargin_2[1]));
      y->size[1] = nm1d2 + 1;
      emxEnsureCapacity_real_T(y, i11);
      for (i11 = 0; i11 <= nm1d2; i11++) {
        y->data[i11] = -varargin_2[1] + (double)i11;
      }
    } else {
      ndbl = std::floor((varargin_1_idx_0 - (-varargin_2[1])) + 0.5);
      apnd = -varargin_2[1] + ndbl;
      cdiff = apnd - varargin_1_idx_0;
      b_u0 = std::abs(-varargin_2[1]);
      u1 = std::abs(varargin_1_idx_0);
      if ((b_u0 > u1) || rtIsNaN(u1)) {
        u1 = b_u0;
      }

      if (std::abs(cdiff) < 4.4408920985006262E-16 * u1) {
        ndbl++;
        apnd = varargin_1_idx_0;
      } else if (cdiff > 0.0) {
        apnd = -varargin_2[1] + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i11 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = n;
      emxEnsureCapacity_real_T(y, i11);
      if (n > 0) {
        y->data[0] = -varargin_2[1];
        if (n > 1) {
          y->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 0; k <= nm1d2 - 2; k++) {
            y->data[1 + k] = -varargin_2[1] + (1.0 + (double)k);
            y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
          }

          if (nm1d2 << 1 == n - 1) {
            y->data[nm1d2] = (-varargin_2[1] + apnd) / 2.0;
          } else {
            y->data[nm1d2] = -varargin_2[1] + (double)nm1d2;
            y->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    varargin_1_idx_0 = 2.0 * (double)(unsigned int)sizeA_idx_1;
    b_mod(y, varargin_1_idx_0, b_y);
    i11 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = b_y->size[1];
    emxEnsureCapacity_uint32_T(idxDir, i11);
    nm1d2 = b_y->size[0] * b_y->size[1];
    for (i11 = 0; i11 < nm1d2; i11++) {
      idxDir->data[i11] = dimNums->data[(int)(b_y->data[i11] + 1.0) - 1];
    }

    emxFree_uint32_T(&dimNums);
    b_mod(y, varargin_1_idx_0, b_y);
    if (1 > b_y->size[1]) {
      nm1d2 = 0;
    } else {
      b_mod(y, varargin_1_idx_0, b_y);
      nm1d2 = b_y->size[1];
    }

    emxFree_real_T(&b_y);
    emxFree_real_T(&y);
    i11 = r2->size[0];
    r2->size[0] = nm1d2;
    emxEnsureCapacity_int32_T(r2, i11);
    for (i11 = 0; i11 < nm1d2; i11++) {
      r2->data[i11] = i11;
    }

    nm1d2 = r2->size[0];
    for (i11 = 0; i11 < nm1d2; i11++) {
      idxA->data[r2->data[i11] + idxA->size[0]] = (int)idxDir->data[i11];
    }

    emxFree_int32_T(&r2);
    emxFree_uint32_T(&idxDir);
    sizeA_idx_0 = (double)varargin_1->size[0] + 2.0 * varargin_2[0];
    sizeA_idx_1 = (double)varargin_1->size[1] + 2.0 * varargin_2[1];
    i11 = b->size[0] * b->size[1];
    b->size[0] = (int)sizeA_idx_0;
    b->size[1] = (int)sizeA_idx_1;
    emxEnsureCapacity_real_T(b, i11);
    i11 = b->size[1];
    for (nm1d2 = 0; nm1d2 < i11; nm1d2++) {
      k = b->size[0];
      for (n = 0; n < k; n++) {
        b->data[n + b->size[0] * nm1d2] = varargin_1->data[(idxA->data[n] +
          varargin_1->size[0] * (idxA->data[nm1d2 + idxA->size[0]] - 1)) - 1];
      }
    }

    emxFree_int32_T(&idxA);
  }
}

void padarray(const emxArray_real_T *varargin_1, const double varargin_2[2],
              emxArray_real_T *b)
{
  double sizeA_idx_0;
  double sizeA_idx_1;
  unsigned int sizeA_idx_0_tmp;
  double sizeA[2];
  unsigned int sizeA_idx_1_tmp;
  double varargin_1_idx_0;
  double varargin_1_idx_1;
  emxArray_int32_T *idxA;
  emxArray_int8_T *onesVector;
  int i7;
  int loop_ub;
  emxArray_real_T *y;
  emxArray_uint32_T *idxDir;
  emxArray_int32_T *r1;
  int i8;
  int i;
  if ((varargin_1->size[0] == 0) || (varargin_1->size[1] == 0)) {
    sizeA_idx_0 = (double)varargin_1->size[0] + 2.0 * varargin_2[0];
    sizeA_idx_1 = (double)varargin_1->size[1] + 2.0 * varargin_2[1];
    sizeA[0] = sizeA_idx_0;
    sizeA[1] = sizeA_idx_1;
    repmat(sizeA, b);
  } else {
    sizeA_idx_0 = varargin_1->size[0];
    sizeA_idx_1 = varargin_1->size[1];
    sizeA_idx_0_tmp = (unsigned int)sizeA_idx_0;
    sizeA_idx_1_tmp = (unsigned int)sizeA_idx_1;
    varargin_1_idx_0 = 2.0 * varargin_2[0] + (double)sizeA_idx_0_tmp;
    varargin_1_idx_1 = 2.0 * varargin_2[1] + (double)sizeA_idx_1_tmp;
    if ((varargin_1_idx_0 < varargin_1_idx_1) || (rtIsNaN(varargin_1_idx_0) && (
          !rtIsNaN(varargin_1_idx_1)))) {
      varargin_1_idx_0 = varargin_1_idx_1;
    }

    emxInit_int32_T(&idxA, 2);
    emxInit_int8_T(&onesVector, 2);
    i7 = idxA->size[0] * idxA->size[1];
    idxA->size[0] = (int)varargin_1_idx_0;
    idxA->size[1] = 2;
    emxEnsureCapacity_int32_T(idxA, i7);
    i7 = onesVector->size[0] * onesVector->size[1];
    onesVector->size[0] = 1;
    loop_ub = (int)varargin_2[0];
    onesVector->size[1] = loop_ub;
    emxEnsureCapacity_int8_T(onesVector, i7);
    for (i7 = 0; i7 < loop_ub; i7++) {
      onesVector->data[i7] = 1;
    }

    emxInit_real_T(&y, 2);
    i7 = y->size[0] * y->size[1];
    y->size[0] = 1;
    loop_ub = (int)((double)(unsigned int)sizeA_idx_0 - 1.0);
    y->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(y, i7);
    for (i7 = 0; i7 <= loop_ub; i7++) {
      y->data[i7] = 1.0 + (double)i7;
    }

    emxInit_uint32_T(&idxDir, 2);
    i7 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = (onesVector->size[1] + y->size[1]) + onesVector->size[1];
    emxEnsureCapacity_uint32_T(idxDir, i7);
    loop_ub = onesVector->size[1];
    for (i7 = 0; i7 < loop_ub; i7++) {
      idxDir->data[i7] = (unsigned int)onesVector->data[i7];
    }

    loop_ub = y->size[1];
    for (i7 = 0; i7 < loop_ub; i7++) {
      idxDir->data[i7 + onesVector->size[1]] = (unsigned int)rt_roundd_snf
        (y->data[i7]);
    }

    loop_ub = onesVector->size[1];
    for (i7 = 0; i7 < loop_ub; i7++) {
      idxDir->data[(i7 + onesVector->size[1]) + y->size[1]] = sizeA_idx_0_tmp *
        onesVector->data[i7];
    }

    emxInit_int32_T(&r1, 1);
    loop_ub = idxDir->size[1];
    i7 = r1->size[0];
    r1->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r1, i7);
    for (i7 = 0; i7 < loop_ub; i7++) {
      r1->data[i7] = i7;
    }

    loop_ub = r1->size[0];
    for (i7 = 0; i7 < loop_ub; i7++) {
      idxA->data[r1->data[i7]] = (int)idxDir->data[i7];
    }

    i7 = onesVector->size[0] * onesVector->size[1];
    onesVector->size[0] = 1;
    loop_ub = (int)varargin_2[1];
    onesVector->size[1] = loop_ub;
    emxEnsureCapacity_int8_T(onesVector, i7);
    for (i7 = 0; i7 < loop_ub; i7++) {
      onesVector->data[i7] = 1;
    }

    i7 = y->size[0] * y->size[1];
    y->size[0] = 1;
    loop_ub = (int)((double)(unsigned int)sizeA_idx_1 - 1.0);
    y->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(y, i7);
    for (i7 = 0; i7 <= loop_ub; i7++) {
      y->data[i7] = 1.0 + (double)i7;
    }

    i7 = idxDir->size[0] * idxDir->size[1];
    idxDir->size[0] = 1;
    idxDir->size[1] = (onesVector->size[1] + y->size[1]) + onesVector->size[1];
    emxEnsureCapacity_uint32_T(idxDir, i7);
    loop_ub = onesVector->size[1];
    for (i7 = 0; i7 < loop_ub; i7++) {
      idxDir->data[i7] = (unsigned int)onesVector->data[i7];
    }

    loop_ub = y->size[1];
    for (i7 = 0; i7 < loop_ub; i7++) {
      idxDir->data[i7 + onesVector->size[1]] = (unsigned int)rt_roundd_snf
        (y->data[i7]);
    }

    loop_ub = onesVector->size[1];
    for (i7 = 0; i7 < loop_ub; i7++) {
      idxDir->data[(i7 + onesVector->size[1]) + y->size[1]] = sizeA_idx_1_tmp *
        onesVector->data[i7];
    }

    emxFree_real_T(&y);
    emxFree_int8_T(&onesVector);
    loop_ub = idxDir->size[1];
    i7 = r1->size[0];
    r1->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r1, i7);
    for (i7 = 0; i7 < loop_ub; i7++) {
      r1->data[i7] = i7;
    }

    loop_ub = r1->size[0];
    for (i7 = 0; i7 < loop_ub; i7++) {
      idxA->data[r1->data[i7] + idxA->size[0]] = (int)idxDir->data[i7];
    }

    emxFree_int32_T(&r1);
    emxFree_uint32_T(&idxDir);
    sizeA_idx_0 = (double)varargin_1->size[0] + 2.0 * varargin_2[0];
    sizeA_idx_1 = (double)varargin_1->size[1] + 2.0 * varargin_2[1];
    i7 = b->size[0] * b->size[1];
    b->size[0] = (int)sizeA_idx_0;
    b->size[1] = (int)sizeA_idx_1;
    emxEnsureCapacity_real_T(b, i7);
    i7 = b->size[1];
    for (loop_ub = 0; loop_ub < i7; loop_ub++) {
      i8 = b->size[0];
      for (i = 0; i < i8; i++) {
        b->data[i + b->size[0] * loop_ub] = varargin_1->data[(idxA->data[i] +
          varargin_1->size[0] * (idxA->data[loop_ub + idxA->size[0]] - 1)) - 1];
      }
    }

    emxFree_int32_T(&idxA);
  }
}

/* End of code generation (padarray.cpp) */
