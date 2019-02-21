/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * imfilter.cpp
 *
 * Code generation for function 'imfilter'
 *
 */
#include "pch.h"
/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "imfilter.h"
#include "Threshold_emxutil.h"
#include "diag.h"
#include "svd.h"
#include "padarray.h"
#include "sum.h"
#include "libmwimfilter.h"
#include "libmwippfilter.h"

/* Function Definitions */
void imfilter(emxArray_real_T *varargin_1, const emxArray_real_T *varargin_2)
{
  double outSizeT[2];
  double filter_center[2];
  double startT[2];
  emxArray_real_T *a;
  emxArray_real_T *s;
  emxArray_real_T *unusedU1;
  emxArray_real_T *b_s;
  emxArray_boolean_T *b;
  emxArray_boolean_T *connb;
  emxArray_real_T *c_s;
  boolean_T densityFlag;
  boolean_T x[2];
  emxArray_real_T *nonzero_h;
  int k;
  emxArray_int32_T *r5;
  boolean_T exitg1;
  emxArray_real_T *v;
  int u1;
  int i12;
  int idx;
  int n;
  emxArray_real_T *hcol;
  double tol;
  emxArray_boolean_T *b_connb;
  emxArray_real_T *hrow;
  boolean_T tooBig;
  double out_size_row[2];
  double start[2];
  double padSizeT[2];
  emxArray_boolean_T *c_connb;
  emxArray_int32_T *r6;
  outSizeT[0] = varargin_1->size[0];
  filter_center[0] = std::floor(((double)varargin_2->size[0] + 1.0) / 2.0);
  startT[0] = (double)varargin_2->size[0] - filter_center[0];
  outSizeT[1] = varargin_1->size[1];
  filter_center[1] = std::floor(((double)varargin_2->size[1] + 1.0) / 2.0);
  startT[1] = (double)varargin_2->size[1] - filter_center[1];
  if ((varargin_1->size[0] != 0) && (varargin_1->size[1] != 0)) {
    emxInit_real_T(&a, 2);
    emxInit_real_T(&s, 2);
    emxInit_real_T(&unusedU1, 2);
    emxInit_real_T(&b_s, 1);
    emxInit_boolean_T(&b, 1);
    emxInit_boolean_T(&connb, 1);
    emxInit_real_T(&c_s, 2);
    if (varargin_2->size[0] * varargin_2->size[1] >= 49) {
      x[0] = (varargin_2->size[0] != 1);
      x[1] = (varargin_2->size[1] != 1);
      densityFlag = true;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k < 2)) {
        if (!x[k]) {
          densityFlag = false;
          exitg1 = true;
        } else {
          k++;
        }
      }

      if (densityFlag) {
        i12 = b->size[0];
        b->size[0] = varargin_2->size[0] * varargin_2->size[1];
        emxEnsureCapacity_boolean_T(b, i12);
        idx = varargin_2->size[0] * varargin_2->size[1];
        for (i12 = 0; i12 < idx; i12++) {
          b->data[i12] = rtIsInf(varargin_2->data[i12]);
        }

        i12 = connb->size[0];
        connb->size[0] = varargin_2->size[0] * varargin_2->size[1];
        emxEnsureCapacity_boolean_T(connb, i12);
        idx = varargin_2->size[0] * varargin_2->size[1];
        for (i12 = 0; i12 < idx; i12++) {
          connb->data[i12] = rtIsNaN(varargin_2->data[i12]);
        }

        i12 = b->size[0];
        emxEnsureCapacity_boolean_T(b, i12);
        idx = b->size[0];
        for (i12 = 0; i12 < idx; i12++) {
          b->data[i12] = ((!b->data[i12]) && (!connb->data[i12]));
        }

        densityFlag = true;
        idx = 1;
        exitg1 = false;
        while ((!exitg1) && (idx <= b->size[0])) {
          if (!b->data[idx - 1]) {
            densityFlag = false;
            exitg1 = true;
          } else {
            idx++;
          }
        }

        if (densityFlag) {
          svd(varargin_2, a, s, unusedU1);
          idx = s->size[0];
          k = s->size[1];
          i12 = c_s->size[0] * c_s->size[1];
          c_s->size[0] = idx;
          c_s->size[1] = k;
          emxEnsureCapacity_real_T(c_s, i12);
          for (i12 = 0; i12 < k; i12++) {
            for (n = 0; n < idx; n++) {
              c_s->data[n + c_s->size[0] * i12] = s->data[n + s->size[0] * i12];
            }
          }

          diag(c_s, b_s);
          idx = varargin_2->size[0];
          u1 = varargin_2->size[1];
          if (idx > u1) {
            u1 = idx;
          }

          n = b_s->size[0];
          if (b_s->size[0] <= 2) {
            if (b_s->size[0] == 1) {
              tol = b_s->data[0];
            } else if ((b_s->data[0] < b_s->data[1]) || (rtIsNaN(b_s->data[0]) &&
                        (!rtIsNaN(b_s->data[1])))) {
              tol = b_s->data[1];
            } else {
              tol = b_s->data[0];
            }
          } else {
            if (!rtIsNaN(b_s->data[0])) {
              idx = 1;
            } else {
              idx = 0;
              k = 2;
              exitg1 = false;
              while ((!exitg1) && (k <= b_s->size[0])) {
                if (!rtIsNaN(b_s->data[k - 1])) {
                  idx = k;
                  exitg1 = true;
                } else {
                  k++;
                }
              }
            }

            if (idx == 0) {
              tol = b_s->data[0];
            } else {
              tol = b_s->data[idx - 1];
              i12 = idx + 1;
              for (k = i12; k <= n; k++) {
                if (tol < b_s->data[k - 1]) {
                  tol = b_s->data[k - 1];
                }
              }
            }
          }

          tol = (double)u1 * tol * 2.2204460492503131E-16;
          i12 = b->size[0];
          b->size[0] = b_s->size[0];
          emxEnsureCapacity_boolean_T(b, i12);
          idx = b_s->size[0];
          for (i12 = 0; i12 < idx; i12++) {
            b->data[i12] = (b_s->data[i12] > tol);
          }

          densityFlag = (sum(b) == 1.0);
        } else {
          densityFlag = false;
        }
      } else {
        densityFlag = false;
      }
    } else {
      densityFlag = false;
    }

    emxFree_boolean_T(&b);
    emxInit_real_T(&nonzero_h, 1);
    emxInit_int32_T(&r5, 1);
    if (densityFlag) {
      emxInit_real_T(&v, 2);
      padarray(varargin_1, startT, a);
      svd(varargin_2, unusedU1, s, v);
      idx = s->size[0];
      k = s->size[1];
      i12 = c_s->size[0] * c_s->size[1];
      c_s->size[0] = idx;
      c_s->size[1] = k;
      emxEnsureCapacity_real_T(c_s, i12);
      for (i12 = 0; i12 < k; i12++) {
        for (n = 0; n < idx; n++) {
          c_s->data[n + c_s->size[0] * i12] = s->data[n + s->size[0] * i12];
        }
      }

      emxInit_real_T(&hcol, 1);
      diag(c_s, b_s);
      tol = std::sqrt(b_s->data[0]);
      idx = unusedU1->size[0];
      i12 = hcol->size[0];
      hcol->size[0] = idx;
      emxEnsureCapacity_real_T(hcol, i12);
      for (i12 = 0; i12 < idx; i12++) {
        hcol->data[i12] = unusedU1->data[i12] * tol;
      }

      emxInit_real_T(&hrow, 2);
      tol = std::sqrt(b_s->data[0]);
      idx = v->size[0];
      i12 = hrow->size[0] * hrow->size[1];
      hrow->size[0] = 1;
      hrow->size[1] = idx;
      emxEnsureCapacity_real_T(hrow, i12);
      for (i12 = 0; i12 < idx; i12++) {
        hrow->data[i12] = v->data[i12] * tol;
      }

      emxFree_real_T(&v);
      out_size_row[0] = a->size[0];
      out_size_row[1] = outSizeT[1];
      start[0] = 0.0;
      start[1] = (int)startT[1];
      i12 = connb->size[0];
      connb->size[0] = hrow->size[1];
      emxEnsureCapacity_boolean_T(connb, i12);
      idx = hrow->size[1];
      for (i12 = 0; i12 < idx; i12++) {
        connb->data[i12] = (hrow->data[i12] != 0.0);
      }

      u1 = connb->size[0] - 1;
      k = 0;
      for (n = 0; n <= u1; n++) {
        if (connb->data[n]) {
          k++;
        }
      }

      i12 = r5->size[0];
      r5->size[0] = k;
      emxEnsureCapacity_int32_T(r5, i12);
      idx = 0;
      for (n = 0; n <= u1; n++) {
        if (connb->data[n]) {
          r5->data[idx] = n + 1;
          idx++;
        }
      }

      i12 = nonzero_h->size[0];
      nonzero_h->size[0] = r5->size[0];
      emxEnsureCapacity_real_T(nonzero_h, i12);
      idx = r5->size[0];
      for (i12 = 0; i12 < idx; i12++) {
        nonzero_h->data[i12] = hrow->data[r5->data[i12] - 1];
      }

      emxInit_boolean_T(&c_connb, 2);
      i12 = c_connb->size[0] * c_connb->size[1];
      c_connb->size[0] = 1;
      c_connb->size[1] = hrow->size[1];
      emxEnsureCapacity_boolean_T(c_connb, i12);
      idx = hrow->size[0] * hrow->size[1];
      for (i12 = 0; i12 < idx; i12++) {
        c_connb->data[i12] = (hrow->data[i12] != 0.0);
      }

      densityFlag = false;
      if ((double)r5->size[0] / (double)hrow->size[1] > 0.05) {
        densityFlag = true;
      }

      tooBig = (out_size_row[0] > 65500.0);
      if (tooBig && (outSizeT[1] > 65500.0)) {
      } else {
        tooBig = false;
      }

      if (densityFlag && (!tooBig)) {
        densityFlag = true;
      } else {
        densityFlag = false;
      }

      i12 = varargin_1->size[0] * varargin_1->size[1];
      varargin_1->size[0] = (int)out_size_row[0];
      varargin_1->size[1] = (int)outSizeT[1];
      emxEnsureCapacity_real_T(varargin_1, i12);
      if (densityFlag) {
        padSizeT[0] = a->size[0];
        filter_center[0] = hrow->size[0];
        padSizeT[1] = a->size[1];
        filter_center[1] = hrow->size[1];
        ippfilter_real64(&a->data[0], &varargin_1->data[0], out_size_row, 2.0,
                         padSizeT, &hrow->data[0], filter_center, false);
      } else {
        padSizeT[0] = a->size[0];
        filter_center[0] = c_connb->size[0];
        padSizeT[1] = a->size[1];
        filter_center[1] = c_connb->size[1];
        imfilter_real64(&a->data[0], &varargin_1->data[0], 2.0, out_size_row,
                        2.0, padSizeT, &nonzero_h->data[0], (double)r5->size[0],
                        &c_connb->data[0], 2.0, filter_center, start, 2.0, true,
                        false);
      }

      emxFree_boolean_T(&c_connb);
      emxFree_real_T(&hrow);
      start[0] = (int)startT[0];
      start[1] = 0.0;
      i12 = connb->size[0];
      connb->size[0] = hcol->size[0];
      emxEnsureCapacity_boolean_T(connb, i12);
      idx = hcol->size[0];
      for (i12 = 0; i12 < idx; i12++) {
        connb->data[i12] = (hcol->data[i12] != 0.0);
      }

      u1 = connb->size[0] - 1;
      k = 0;
      for (n = 0; n <= u1; n++) {
        if (connb->data[n]) {
          k++;
        }
      }

      emxInit_int32_T(&r6, 1);
      i12 = r6->size[0];
      r6->size[0] = k;
      emxEnsureCapacity_int32_T(r6, i12);
      idx = 0;
      for (n = 0; n <= u1; n++) {
        if (connb->data[n]) {
          r6->data[idx] = n + 1;
          idx++;
        }
      }

      i12 = nonzero_h->size[0];
      nonzero_h->size[0] = r6->size[0];
      emxEnsureCapacity_real_T(nonzero_h, i12);
      idx = r6->size[0];
      for (i12 = 0; i12 < idx; i12++) {
        nonzero_h->data[i12] = hcol->data[r6->data[i12] - 1];
      }

      i12 = connb->size[0];
      connb->size[0] = hcol->size[0];
      emxEnsureCapacity_boolean_T(connb, i12);
      idx = hcol->size[0];
      for (i12 = 0; i12 < idx; i12++) {
        connb->data[i12] = (hcol->data[i12] != 0.0);
      }

      densityFlag = false;
      if ((double)r6->size[0] / (double)hcol->size[0] > 0.05) {
        densityFlag = true;
      }

      tooBig = (outSizeT[0] > 65500.0);
      if (tooBig && (outSizeT[1] > 65500.0)) {
      } else {
        tooBig = false;
      }

      if (densityFlag && (!tooBig)) {
        densityFlag = true;
      } else {
        densityFlag = false;
      }

      i12 = a->size[0] * a->size[1];
      a->size[0] = varargin_1->size[0];
      a->size[1] = varargin_1->size[1];
      emxEnsureCapacity_real_T(a, i12);
      idx = varargin_1->size[0] * varargin_1->size[1];
      for (i12 = 0; i12 < idx; i12++) {
        a->data[i12] = varargin_1->data[i12];
      }

      i12 = varargin_1->size[0] * varargin_1->size[1];
      varargin_1->size[0] = (int)outSizeT[0];
      varargin_1->size[1] = (int)outSizeT[1];
      emxEnsureCapacity_real_T(varargin_1, i12);
      if (densityFlag) {
        padSizeT[0] = a->size[0];
        padSizeT[1] = a->size[1];
        filter_center[0] = hcol->size[0];
        filter_center[1] = 1.0;
        ippfilter_real64(&a->data[0], &varargin_1->data[0], outSizeT, 2.0,
                         padSizeT, &hcol->data[0], filter_center, false);
      } else {
        padSizeT[0] = a->size[0];
        padSizeT[1] = a->size[1];
        filter_center[0] = connb->size[0];
        filter_center[1] = 1.0;
        imfilter_real64(&a->data[0], &varargin_1->data[0], 2.0, outSizeT, 2.0,
                        padSizeT, &nonzero_h->data[0], (double)r6->size[0],
                        &connb->data[0], 2.0, filter_center, start, 2.0, true,
                        false);
      }

      emxFree_int32_T(&r6);
      emxFree_real_T(&hcol);
    } else {
      padarray(varargin_1, startT, a);
      if ((varargin_2->size[0] == 1) || (varargin_2->size[1] == 1)) {
        i12 = connb->size[0];
        connb->size[0] = varargin_2->size[0] * varargin_2->size[1];
        emxEnsureCapacity_boolean_T(connb, i12);
        idx = varargin_2->size[0] * varargin_2->size[1];
        for (i12 = 0; i12 < idx; i12++) {
          connb->data[i12] = (varargin_2->data[i12] != 0.0);
        }

        u1 = connb->size[0] - 1;
        k = 0;
        for (n = 0; n <= u1; n++) {
          if (connb->data[n]) {
            k++;
          }
        }

        i12 = nonzero_h->size[0];
        nonzero_h->size[0] = k;
        emxEnsureCapacity_real_T(nonzero_h, i12);
        idx = 0;
        for (n = 0; n <= u1; n++) {
          if (connb->data[n]) {
            nonzero_h->data[idx] = varargin_2->data[n];
            idx++;
          }
        }
      } else {
        u1 = varargin_2->size[0] * varargin_2->size[1] - 1;
        k = 0;
        for (n = 0; n <= u1; n++) {
          if (varargin_2->data[n] != 0.0) {
            k++;
          }
        }

        i12 = r5->size[0];
        r5->size[0] = k;
        emxEnsureCapacity_int32_T(r5, i12);
        idx = 0;
        for (n = 0; n <= u1; n++) {
          if (varargin_2->data[n] != 0.0) {
            r5->data[idx] = n + 1;
            idx++;
          }
        }

        i12 = nonzero_h->size[0];
        nonzero_h->size[0] = r5->size[0];
        emxEnsureCapacity_real_T(nonzero_h, i12);
        idx = r5->size[0];
        for (i12 = 0; i12 < idx; i12++) {
          nonzero_h->data[i12] = varargin_2->data[r5->data[i12] - 1];
        }
      }

      emxInit_boolean_T(&b_connb, 2);
      i12 = b_connb->size[0] * b_connb->size[1];
      b_connb->size[0] = varargin_2->size[0];
      b_connb->size[1] = varargin_2->size[1];
      emxEnsureCapacity_boolean_T(b_connb, i12);
      idx = varargin_2->size[0] * varargin_2->size[1];
      for (i12 = 0; i12 < idx; i12++) {
        b_connb->data[i12] = (varargin_2->data[i12] != 0.0);
      }

      densityFlag = false;
      if ((double)nonzero_h->size[0] / (double)(varargin_2->size[0] *
           varargin_2->size[1]) > 0.05) {
        densityFlag = true;
      }

      tooBig = (outSizeT[0] > 65500.0);
      if (tooBig && (outSizeT[1] > 65500.0)) {
      } else {
        tooBig = false;
      }

      if (densityFlag && (!tooBig)) {
        densityFlag = true;
      } else {
        densityFlag = false;
      }

      i12 = varargin_1->size[0] * varargin_1->size[1];
      varargin_1->size[0] = (int)outSizeT[0];
      varargin_1->size[1] = (int)outSizeT[1];
      emxEnsureCapacity_real_T(varargin_1, i12);
      if (densityFlag) {
        padSizeT[0] = a->size[0];
        padSizeT[1] = a->size[1];
        filter_center[0] = varargin_2->size[0];
        filter_center[1] = varargin_2->size[1];
        ippfilter_real64(&a->data[0], &varargin_1->data[0], outSizeT, 2.0,
                         padSizeT, &varargin_2->data[0], filter_center, false);
      } else {
        padSizeT[0] = a->size[0];
        filter_center[0] = b_connb->size[0];
        padSizeT[1] = a->size[1];
        filter_center[1] = b_connb->size[1];
        imfilter_real64(&a->data[0], &varargin_1->data[0], 2.0, outSizeT, 2.0,
                        padSizeT, &nonzero_h->data[0], (double)nonzero_h->size[0],
                        &b_connb->data[0], 2.0, filter_center, startT, 2.0, true,
                        false);
      }

      emxFree_boolean_T(&b_connb);
    }

    emxFree_real_T(&c_s);
    emxFree_boolean_T(&connb);
    emxFree_int32_T(&r5);
    emxFree_real_T(&nonzero_h);
    emxFree_real_T(&b_s);
    emxFree_real_T(&unusedU1);
    emxFree_real_T(&s);
    emxFree_real_T(&a);
  }
}

/* End of code generation (imfilter.cpp) */
