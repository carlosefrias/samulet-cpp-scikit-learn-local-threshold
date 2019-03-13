/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * adaptthresh.cpp
 *
 * Code generation for function 'adaptthresh'
 *
 */
#include "pch.h"
/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include <string.h>
#include <float.h>
#include "Threshold.h"
#include "adaptthresh.h"
#include "Threshold_emxutil.h"
#include "imfilter.h"
#include "ordfilt2.h"
#include "useConstantDim.h"
#include "padarray.h"
#include "libmwboxfilter.h"
#include "libmwimlincomb_tbb.h"

/* Function Declarations */
static void localGaussThresh(const emxArray_real_T *b_I, const double nhoodSize
  [2], double scaleFactor, emxArray_real_T *T);
static void parseOptionalInputs(const emxArray_uint16_T *b_I, double varargin_1,
  const char varargin_5_data[], const int varargin_5_size[2], double
  *sensitivity, char statistic_data[], int statistic_size[2], double nhoodSize[2]);
static double rt_remd_snf(double u0, double u1);

/* Function Definitions */
static void localGaussThresh(const emxArray_real_T *b_I, const double nhoodSize
  [2], double scaleFactor, emxArray_real_T *T)
{
  emxArray_real_T *y;
  double filterRadius_idx_0;
  double filterRadius_idx_1;
  int i;
  double ndbl;
  double apnd;
  double cdiff;
  int nm1d2;
  emxArray_real_T *b_y;
  double u0;
  double u1;
  emxArray_real_T *h;
  emxArray_real_T *Y;
  int nx;
  int n;
  int ny;
  boolean_T exitg1;
  emxArray_boolean_T *r3;
  emxArray_int32_T *r4;
  emxInit_real_T(&y, 2);
  filterRadius_idx_0 = ((2.0 * std::ceil(2.0 * nhoodSize[0]) + 1.0) - 1.0) / 2.0;
  filterRadius_idx_1 = ((2.0 * std::ceil(2.0 * nhoodSize[1]) + 1.0) - 1.0) / 2.0;
  if (rtIsNaN(-filterRadius_idx_1) || rtIsNaN(filterRadius_idx_1)) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i);
    y->data[0] = rtNaN;
  } else if (filterRadius_idx_1 < -filterRadius_idx_1) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if ((rtIsInf(-filterRadius_idx_1) || rtIsInf(filterRadius_idx_1)) &&
             (-filterRadius_idx_1 == filterRadius_idx_1)) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i);
    y->data[0] = rtNaN;
  } else if (std::floor(-filterRadius_idx_1) == -filterRadius_idx_1) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    nm1d2 = (int)std::floor(filterRadius_idx_1 - (-filterRadius_idx_1));
    y->size[1] = nm1d2 + 1;
    emxEnsureCapacity_real_T(y, i);
    for (i = 0; i <= nm1d2; i++) {
      y->data[i] = -filterRadius_idx_1 + (double)i;
    }
  } else {
    ndbl = std::floor((filterRadius_idx_1 - (-filterRadius_idx_1)) + 0.5);
    apnd = -filterRadius_idx_1 + ndbl;
    cdiff = apnd - filterRadius_idx_1;
    u0 = std::abs(-filterRadius_idx_1);
    u1 = std::abs(filterRadius_idx_1);
    if ((u0 > u1) || rtIsNaN(u1)) {
      u1 = u0;
    }

    if (std::abs(cdiff) < 4.4408920985006262E-16 * u1) {
      ndbl++;
      apnd = filterRadius_idx_1;
    } else if (cdiff > 0.0) {
      apnd = -filterRadius_idx_1 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }

    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_real_T(y, i);
    if (n > 0) {
      y->data[0] = -filterRadius_idx_1;
      if (n > 1) {
        y->data[n - 1] = apnd;
        nm1d2 = (n - 1) / 2;
        for (ny = 0; ny <= nm1d2 - 2; ny++) {
          y->data[1 + ny] = -filterRadius_idx_1 + (1.0 + (double)ny);
          y->data[(n - ny) - 2] = apnd - (1.0 + (double)ny);
        }

        if (nm1d2 << 1 == n - 1) {
          y->data[nm1d2] = (-filterRadius_idx_1 + apnd) / 2.0;
        } else {
          y->data[nm1d2] = -filterRadius_idx_1 + (double)nm1d2;
          y->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }
  }

  emxInit_real_T(&b_y, 2);
  if (rtIsNaN(-filterRadius_idx_0) || rtIsNaN(filterRadius_idx_0)) {
    i = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = 1;
    emxEnsureCapacity_real_T(b_y, i);
    b_y->data[0] = rtNaN;
  } else if (filterRadius_idx_0 < -filterRadius_idx_0) {
    b_y->size[0] = 1;
    b_y->size[1] = 0;
  } else if ((rtIsInf(-filterRadius_idx_0) || rtIsInf(filterRadius_idx_0)) &&
             (-filterRadius_idx_0 == filterRadius_idx_0)) {
    i = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = 1;
    emxEnsureCapacity_real_T(b_y, i);
    b_y->data[0] = rtNaN;
  } else if (std::floor(-filterRadius_idx_0) == -filterRadius_idx_0) {
    i = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    nm1d2 = (int)std::floor(filterRadius_idx_0 - (-filterRadius_idx_0));
    b_y->size[1] = nm1d2 + 1;
    emxEnsureCapacity_real_T(b_y, i);
    for (i = 0; i <= nm1d2; i++) {
      b_y->data[i] = -filterRadius_idx_0 + (double)i;
    }
  } else {
    ndbl = std::floor((filterRadius_idx_0 - (-filterRadius_idx_0)) + 0.5);
    apnd = -filterRadius_idx_0 + ndbl;
    cdiff = apnd - filterRadius_idx_0;
    u0 = std::abs(-filterRadius_idx_0);
    u1 = std::abs(filterRadius_idx_0);
    if ((u0 > u1) || rtIsNaN(u1)) {
      u1 = u0;
    }

    if (std::abs(cdiff) < 4.4408920985006262E-16 * u1) {
      ndbl++;
      apnd = filterRadius_idx_0;
    } else if (cdiff > 0.0) {
      apnd = -filterRadius_idx_0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }

    i = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = n;
    emxEnsureCapacity_real_T(b_y, i);
    if (n > 0) {
      b_y->data[0] = -filterRadius_idx_0;
      if (n > 1) {
        b_y->data[n - 1] = apnd;
        nm1d2 = (n - 1) / 2;
        for (ny = 0; ny <= nm1d2 - 2; ny++) {
          b_y->data[1 + ny] = -filterRadius_idx_0 + (1.0 + (double)ny);
          b_y->data[(n - ny) - 2] = apnd - (1.0 + (double)ny);
        }

        if (nm1d2 << 1 == n - 1) {
          b_y->data[nm1d2] = (-filterRadius_idx_0 + apnd) / 2.0;
        } else {
          b_y->data[nm1d2] = -filterRadius_idx_0 + (double)nm1d2;
          b_y->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }
  }

  emxInit_real_T(&h, 2);
  emxInit_real_T(&Y, 2);
  nx = y->size[1];
  ny = b_y->size[1];
  nm1d2 = b_y->size[1];
  n = y->size[1];
  i = h->size[0] * h->size[1];
  h->size[0] = nm1d2;
  h->size[1] = n;
  emxEnsureCapacity_real_T(h, i);
  nm1d2 = b_y->size[1];
  n = y->size[1];
  i = Y->size[0] * Y->size[1];
  Y->size[0] = nm1d2;
  Y->size[1] = n;
  emxEnsureCapacity_real_T(Y, i);
  for (nm1d2 = 0; nm1d2 < nx; nm1d2++) {
    for (i = 0; i < ny; i++) {
      h->data[i + h->size[0] * nm1d2] = y->data[nm1d2];
      Y->data[i + Y->size[0] * nm1d2] = b_y->data[i];
    }
  }

  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  i = h->size[0] * h->size[1];
  nm1d2 = h->size[0] * h->size[1];
  emxEnsureCapacity_real_T(h, nm1d2);
  filterRadius_idx_0 = nhoodSize[1] * nhoodSize[1];
  filterRadius_idx_1 = nhoodSize[0] * nhoodSize[0];
  nm1d2 = i - 1;
  for (i = 0; i <= nm1d2; i++) {
    h->data[i] = -(h->data[i] * h->data[i] / filterRadius_idx_0 + Y->data[i] *
                   Y->data[i] / filterRadius_idx_1) / 2.0;
  }

  emxFree_real_T(&Y);
  nx = h->size[0] * h->size[1];
  for (ny = 0; ny < nx; ny++) {
    h->data[ny] = std::exp(h->data[ny]);
  }

  n = h->size[0] * h->size[1];
  if (h->size[0] * h->size[1] <= 2) {
    if (h->size[0] * h->size[1] == 1) {
      filterRadius_idx_0 = h->data[0];
    } else if ((h->data[0] < h->data[1]) || (rtIsNaN(h->data[0]) && (!rtIsNaN
                 (h->data[1])))) {
      filterRadius_idx_0 = h->data[1];
    } else {
      filterRadius_idx_0 = h->data[0];
    }
  } else {
    if (!rtIsNaN(h->data[0])) {
      nm1d2 = 1;
    } else {
      nm1d2 = 0;
      ny = 2;
      exitg1 = false;
      while ((!exitg1) && (ny <= h->size[0] * h->size[1])) {
        if (!rtIsNaN(h->data[ny - 1])) {
          nm1d2 = ny;
          exitg1 = true;
        } else {
          ny++;
        }
      }
    }

    if (nm1d2 == 0) {
      filterRadius_idx_0 = h->data[0];
    } else {
      filterRadius_idx_0 = h->data[nm1d2 - 1];
      i = nm1d2 + 1;
      for (ny = i; ny <= n; ny++) {
        if (filterRadius_idx_0 < h->data[ny - 1]) {
          filterRadius_idx_0 = h->data[ny - 1];
        }
      }
    }
  }

  emxInit_boolean_T(&r3, 2);
  i = r3->size[0] * r3->size[1];
  r3->size[0] = h->size[0];
  r3->size[1] = h->size[1];
  emxEnsureCapacity_boolean_T(r3, i);
  filterRadius_idx_0 *= 2.2204460492503131E-16;
  nm1d2 = h->size[0] * h->size[1];
  for (i = 0; i < nm1d2; i++) {
    r3->data[i] = (h->data[i] < filterRadius_idx_0);
  }

  n = r3->size[0] * r3->size[1] - 1;
  nm1d2 = 0;
  for (i = 0; i <= n; i++) {
    if (r3->data[i]) {
      nm1d2++;
    }
  }

  emxInit_int32_T(&r4, 1);
  i = r4->size[0];
  r4->size[0] = nm1d2;
  emxEnsureCapacity_int32_T(r4, i);
  nm1d2 = 0;
  for (i = 0; i <= n; i++) {
    if (r3->data[i]) {
      r4->data[nm1d2] = i + 1;
      nm1d2++;
    }
  }

  emxFree_boolean_T(&r3);
  nm1d2 = r4->size[0] - 1;
  for (i = 0; i <= nm1d2; i++) {
    h->data[r4->data[i] - 1] = 0.0;
  }

  emxFree_int32_T(&r4);
  nm1d2 = h->size[0] * h->size[1];
  filterRadius_idx_0 = h->data[0];
  for (ny = 2; ny <= nm1d2; ny++) {
    filterRadius_idx_0 += h->data[ny - 1];
  }

  if (filterRadius_idx_0 != 0.0) {
    i = h->size[0] * h->size[1];
    nm1d2 = h->size[0] * h->size[1];
    emxEnsureCapacity_real_T(h, nm1d2);
    nm1d2 = i - 1;
    for (i = 0; i <= nm1d2; i++) {
      h->data[i] /= filterRadius_idx_0;
    }
  }

  i = T->size[0] * T->size[1];
  T->size[0] = b_I->size[0];
  T->size[1] = b_I->size[1];
  emxEnsureCapacity_real_T(T, i);
  nm1d2 = b_I->size[0] * b_I->size[1];
  for (i = 0; i < nm1d2; i++) {
    T->data[i] = b_I->data[i];
  }

  imfilter(T, h);
  i = T->size[0] * T->size[1];
  nm1d2 = T->size[0] * T->size[1];
  emxEnsureCapacity_real_T(T, nm1d2);
  nm1d2 = i - 1;
  emxFree_real_T(&h);
  for (i = 0; i <= nm1d2; i++) {
    T->data[i] *= scaleFactor;
  }
}

static void parseOptionalInputs(const emxArray_real_T *b_I, double varargin_1,
  const char varargin_5_data[], const int varargin_5_size[2], double
  *sensitivity, char statistic_data[], int statistic_size[2], double nhoodSize[2])
{
  double d0;
  int defaultNeighborhoodSize_idx_0;
  int partial_match_size_idx_1;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  boolean_T guard4 = false;
  boolean_T b_bool;
  int minnanb;
  int exitg1;
  int ns;
  boolean_T matched;
  static const char cv5[128] = { '\x00', '\x01', '\x02', '\x03', '\x04', '\x05',
    '\x06', '\x07', '\x08', '	', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f',
    '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18',
    '\x19', '\x1a', '\x1b', '\x1c', '\x1d', '\x1e', '\x1f', ' ', '!', '\"', '#',
    '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2',
    '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'a',
    'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_',
    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}',
    '~', '\x7f' };

  static const char cv6[4] = { 'm', 'e', 'a', 'n' };

  int nmatched;
  boolean_T b_guard1 = false;
  char partial_match_data[8];
  static const char cv7[6] = { 'm', 'e', 'd', 'i', 'a', 'n' };

  static const char vstr[6] = { 'm', 'e', 'd', 'i', 'a', 'n' };

  static const char cv8[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  static const char b_vstr[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  d0 = (double)b_I->size[0] / 16.0;
  d0 = std::floor(d0);
  d0 = 2.0 * d0 + 1.0;
  defaultNeighborhoodSize_idx_0 = (int)d0;
  d0 = (double)b_I->size[1] / 16.0;
  d0 = std::floor(d0);
  d0 = 2.0 * d0 + 1.0;
  *sensitivity = varargin_1;
  partial_match_size_idx_1 = 0;
  guard1 = false;
  guard2 = false;
  guard3 = false;
  guard4 = false;
  if (varargin_5_size[1] <= 4) {
    b_bool = false;
    minnanb = 0;
    do {
      exitg1 = 0;
      if (minnanb < 4) {
        if (cv5[(unsigned char)varargin_5_data[minnanb]] != cv5[(int)cv6[minnanb]])
        {
          exitg1 = 1;
        } else {
          minnanb++;
        }
      } else {
        b_bool = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    if (b_bool) {
      nmatched = 1;
      partial_match_size_idx_1 = 4;
      partial_match_data[0] = 'm';
      partial_match_data[1] = 'e';
      partial_match_data[2] = 'a';
      partial_match_data[3] = 'n';
    } else {
      guard4 = true;
    }
  } else {
    guard4 = true;
  }

  if (guard4) {
    if (varargin_5_size[1] <= 6) {
      ns = varargin_5_size[1];
      b_bool = false;
      minnanb = varargin_5_size[1];
      b_guard1 = false;
      if (ns <= minnanb) {
        if (minnanb < ns) {
          ns = minnanb;
        }

        b_guard1 = true;
      } else {
        if (varargin_5_size[1] == 6) {
          ns = 6;
          b_guard1 = true;
        }
      }

      if (b_guard1) {
        minnanb = 0;
        do {
          exitg1 = 0;
          if (minnanb <= ns - 1) {
            if (cv5[(unsigned char)varargin_5_data[minnanb]] != cv5[(int)
                cv7[minnanb]]) {
              exitg1 = 1;
            } else {
              minnanb++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        if (varargin_5_size[1] == 6) {
          nmatched = 1;
          partial_match_size_idx_1 = 6;
          for (minnanb = 0; minnanb < 6; minnanb++) {
            partial_match_data[minnanb] = vstr[minnanb];
          }
        } else {
          partial_match_size_idx_1 = 6;
          for (minnanb = 0; minnanb < 6; minnanb++) {
            partial_match_data[minnanb] = vstr[minnanb];
          }

          matched = true;
          nmatched = 1;
          guard2 = true;
        }
      } else {
        guard3 = true;
      }
    } else {
      guard3 = true;
    }
  }

  if (guard3) {
    matched = false;
    nmatched = 0;
    guard2 = true;
  }

  if (guard2) {
    ns = varargin_5_size[1];
    b_bool = false;
    minnanb = varargin_5_size[1];
    if (minnanb >= 8) {
      minnanb = 8;
    }

    b_guard1 = false;
    if (ns <= minnanb) {
      if (minnanb < ns) {
        ns = minnanb;
      }

      b_guard1 = true;
    } else {
      if (varargin_5_size[1] == 8) {
        ns = 8;
        b_guard1 = true;
      }
    }

    if (b_guard1) {
      minnanb = 0;
      do {
        exitg1 = 0;
        if (minnanb <= ns - 1) {
          if (cv5[(unsigned char)varargin_5_data[minnanb]] != cv5[(int)
              cv8[minnanb]]) {
            exitg1 = 1;
          } else {
            minnanb++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      if (varargin_5_size[1] == 8) {
        nmatched = 1;
        partial_match_size_idx_1 = 8;
        for (minnanb = 0; minnanb < 8; minnanb++) {
          partial_match_data[minnanb] = b_vstr[minnanb];
        }
      } else {
        if (!matched) {
          partial_match_size_idx_1 = 8;
          for (minnanb = 0; minnanb < 8; minnanb++) {
            partial_match_data[minnanb] = b_vstr[minnanb];
          }
        }

        nmatched++;
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1 && (nmatched == 0)) {
    partial_match_size_idx_1 = 0;
  }

  if ((nmatched == 0) || (partial_match_size_idx_1 == 0)) {
    statistic_size[0] = 1;
    statistic_size[1] = 0;
  } else {
    if (nmatched <= 1) {
      statistic_size[0] = 1;
      statistic_size[1] = partial_match_size_idx_1;
      memcpy(&statistic_data[0], &partial_match_data[0], (unsigned int)
             (partial_match_size_idx_1 * (int)sizeof(char)));
    }
  }

  nhoodSize[0] = defaultNeighborhoodSize_idx_0;
  nhoodSize[1] = (int)d0;
}

static double rt_remd_snf(double u0, double u1)
{
  double y;
  double b_u1;
  double q;
  if (rtIsNaN(u0) || rtIsInf(u0) || (rtIsNaN(u1) || rtIsInf(u1))) {
    y = rtNaN;
  } else {
    if (u1 < 0.0) {
      b_u1 = std::ceil(u1);
    } else {
      b_u1 = std::floor(u1);
    }

    if ((u1 != 0.0) && (u1 != b_u1)) {
      q = std::abs(u0 / u1);
      if (std::abs(q - std::floor(q + 0.5)) <= DBL_EPSILON * q) {
        y = 0.0 * u0;
      } else {
        y = std::fmod(u0, u1);
      }
    } else {
      y = std::fmod(u0, u1);
    }
  }

  return y;
}

void adaptthresh(const emxArray_real_T *I_, double varargin_1, const char
                 varargin_5_data[], const int varargin_5_size[2],
                 emxArray_real_T *T)
{
  double sensitivity;
  char statistic_data[8];
  int statistic_size[2];
  double outputSize[2];
  emxArray_real_T *b_I;
  int i1;
  int loop_ub;
  boolean_T b_bool;
  int exitg1;
  emxArray_real_T *paddedImage;
  static const char cv2[4] = { 'm', 'e', 'a', 'n' };

  emxArray_real_T *intA;
  double normFactor_tmp;
  static const char cv3[6] = { 'm', 'e', 'd', 'i', 'a', 'n' };

  double order1;
  double kernelSizeT[2];
  static const char cv4[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  double imSizeT[2];
  int i2;
  int i3;
  double pre[2];
  int b_loop_ub;
  int i4;
  parseOptionalInputs(I_, varargin_1, varargin_5_data, varargin_5_size,
                      &sensitivity, statistic_data, statistic_size, outputSize);
  if ((I_->size[0] == 0) || (I_->size[1] == 0)) {
    outputSize[0] = I_->size[0];
    outputSize[1] = I_->size[1];
    i1 = T->size[0] * T->size[1];
    T->size[0] = (int)outputSize[0];
    emxEnsureCapacity_real_T(T, i1);
    i1 = T->size[0] * T->size[1];
    T->size[1] = (int)outputSize[1];
    emxEnsureCapacity_real_T(T, i1);
    loop_ub = (int)outputSize[0] * (int)outputSize[1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      T->data[i1] = 0.0;
    }
  } else {
    emxInit_real_T(&b_I, 2);
    i1 = b_I->size[0] * b_I->size[1];
    b_I->size[0] = I_->size[0];
    b_I->size[1] = I_->size[1];
    emxEnsureCapacity_real_T(b_I, i1);
    loop_ub = I_->size[0] * I_->size[1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_I->data[i1] = (double)I_->data[i1] / 65535.0;
    }

    b_bool = false;
    if (statistic_size[1] == 4) {
      loop_ub = 0;
      do {
        exitg1 = 0;
        if (loop_ub < 4) {
          if (statistic_data[loop_ub] != cv2[loop_ub]) {
            exitg1 = 1;
          } else {
            loop_ub++;
          }
        } else {
          b_bool = true;
          exitg1 = 1;
        }
      } while (exitg1 == 0);
    }

    if (b_bool) {
      loop_ub = 0;
    } else {
      b_bool = false;
      if (statistic_size[1] == 6) {
        loop_ub = 0;
        do {
          exitg1 = 0;
          if (loop_ub < 6) {
            if (statistic_data[loop_ub] != cv3[loop_ub]) {
              exitg1 = 1;
            } else {
              loop_ub++;
            }
          } else {
            b_bool = true;
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }

      if (b_bool) {
        loop_ub = 1;
      } else {
        b_bool = false;
        if (statistic_size[1] == 8) {
          loop_ub = 0;
          do {
            exitg1 = 0;
            if (loop_ub < 8) {
              if (statistic_data[loop_ub] != cv4[loop_ub]) {
                exitg1 = 1;
              } else {
                loop_ub++;
              }
            } else {
              b_bool = true;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (b_bool) {
          loop_ub = 2;
        } else {
          loop_ub = -1;
        }
      }
    }

    emxInit_real_T(&paddedImage, 2);
    emxInit_real_T(&intA, 2);
    switch (loop_ub) {
     case 0:
      normFactor_tmp = outputSize[0] * outputSize[1];
      order1 = (0.6 + (1.0 - sensitivity)) / normFactor_tmp;
      kernelSizeT[0] = outputSize[0];
      kernelSizeT[1] = outputSize[1];
      if (normFactor_tmp < 250.0) {
        i1 = T->size[0] * T->size[1];
        T->size[0] = b_I->size[0];
        T->size[1] = b_I->size[1];
        emxEnsureCapacity_real_T(T, i1);
        loop_ub = b_I->size[0] * b_I->size[1];
        for (i1 = 0; i1 < loop_ub; i1++) {
          T->data[i1] = b_I->data[i1];
        }

        i1 = b_I->size[0] * b_I->size[1];
        b_I->size[0] = (int)outputSize[0];
        b_I->size[1] = (int)outputSize[1];
        emxEnsureCapacity_real_T(b_I, i1);
        loop_ub = (int)outputSize[0] * (int)outputSize[1];
        for (i1 = 0; i1 < loop_ub; i1++) {
          b_I->data[i1] = order1;
        }

        imfilter(T, b_I);
      } else {
        imSizeT[0] = (outputSize[0] - 1.0) / 2.0;
        imSizeT[1] = (outputSize[1] - 1.0) / 2.0;
        padarray(b_I, imSizeT, paddedImage);
        if ((paddedImage->size[0] != 0) && (paddedImage->size[1] != 0)) {
          outputSize[0] = paddedImage->size[0];
          outputSize[1] = paddedImage->size[1];
          outputSize[0] = (double)(unsigned int)outputSize[0] + 1.0;
          outputSize[1] = (double)(unsigned int)outputSize[1] + 1.0;
          i1 = intA->size[0] * intA->size[1];
          i2 = (int)outputSize[0];
          intA->size[0] = i2;
          i3 = (int)outputSize[1];
          intA->size[1] = i3;
          emxEnsureCapacity_real_T(intA, i1);
          loop_ub = i2 * i3;
          for (i1 = 0; i1 < loop_ub; i1++) {
            intA->data[i1] = 0.0;
          }

          i1 = (2 <= i2);
          i2 = (2 <= i3);
          useConstantDim(paddedImage, 1);
          useConstantDim(paddedImage, 2);
          loop_ub = paddedImage->size[1];
          for (i3 = 0; i3 < loop_ub; i3++) {
            b_loop_ub = paddedImage->size[0];
            for (i4 = 0; i4 < b_loop_ub; i4++) {
              intA->data[(i1 + i4) + intA->size[0] * (i2 + i3)] =
                paddedImage->data[i4 + paddedImage->size[0] * i3];
            }
          }
        } else {
          intA->size[0] = 0;
          intA->size[1] = 0;
        }

        outputSize[0] = (double)intA->size[0] - kernelSizeT[0];
        outputSize[1] = (double)intA->size[1] - kernelSizeT[1];
        i1 = T->size[0] * T->size[1];
        T->size[0] = (int)outputSize[0];
        T->size[1] = (int)outputSize[1];
        emxEnsureCapacity_real_T(T, i1);
        imSizeT[0] = intA->size[0];
        pre[0] = 1.0;
        imSizeT[1] = intA->size[1];
        pre[1] = 1.0;
        boxfilter_real64(&intA->data[0], imSizeT, kernelSizeT, order1, pre,
                         &T->data[0], outputSize, 1);
      }
      break;

     case 1:
      i1 = paddedImage->size[0] * paddedImage->size[1];
      paddedImage->size[0] = (int)outputSize[0];
      paddedImage->size[1] = (int)outputSize[1];
      emxEnsureCapacity_real_T(paddedImage, i1);
      loop_ub = (int)outputSize[0] * (int)outputSize[1];
      for (i1 = 0; i1 < loop_ub; i1++) {
        paddedImage->data[i1] = 1.0;
      }

      order1 = outputSize[0] * outputSize[1];
      if (rt_remd_snf(order1, 2.0) == 1.0) {
        i1 = T->size[0] * T->size[1];
        T->size[0] = b_I->size[0];
        T->size[1] = b_I->size[1];
        emxEnsureCapacity_real_T(T, i1);
        loop_ub = b_I->size[0] * b_I->size[1];
        for (i1 = 0; i1 < loop_ub; i1++) {
          T->data[i1] = b_I->data[i1];
        }

        ordfilt2(T, (outputSize[0] * outputSize[1] + 1.0) / 2.0, paddedImage);
      } else {
        order1 /= 2.0;
        i1 = intA->size[0] * intA->size[1];
        intA->size[0] = b_I->size[0];
        intA->size[1] = b_I->size[1];
        emxEnsureCapacity_real_T(intA, i1);
        loop_ub = b_I->size[0] * b_I->size[1];
        for (i1 = 0; i1 < loop_ub; i1++) {
          intA->data[i1] = b_I->data[i1];
        }

        ordfilt2(intA, order1, paddedImage);
        ordfilt2(b_I, order1 + 1.0, paddedImage);
        b_bool = (intA->size[0] * intA->size[1] > 500000);
        if (b_bool) {
          outputSize[0] = intA->size[0];
          outputSize[1] = intA->size[1];
          i1 = T->size[0] * T->size[1];
          T->size[0] = (int)outputSize[0];
          T->size[1] = (int)outputSize[1];
          emxEnsureCapacity_real_T(T, i1);
          outputSize[0] = 0.5;
          outputSize[1] = 0.5;
          imlincomb_tbb_real64(outputSize, 2.0, &T->data[0], 0, (double)
                               (intA->size[0] * intA->size[1]), 2.0, &intA->
                               data[0], &b_I->data[0]);
        } else {
          outputSize[0] = intA->size[0];
          outputSize[1] = intA->size[1];
          i1 = T->size[0] * T->size[1];
          T->size[0] = (int)outputSize[0];
          T->size[1] = (int)outputSize[1];
          emxEnsureCapacity_real_T(T, i1);
          i1 = intA->size[0] * intA->size[1];
          for (loop_ub = 0; loop_ub < i1; loop_ub++) {
            T->data[loop_ub] = 0.5 * intA->data[loop_ub] + 0.5 * b_I->
              data[loop_ub];
          }
        }
      }

      i1 = T->size[0] * T->size[1];
      i2 = T->size[0] * T->size[1];
      emxEnsureCapacity_real_T(T, i2);
      loop_ub = i1 - 1;
      for (i1 = 0; i1 <= loop_ub; i1++) {
        T->data[i1] *= 0.6 + (1.0 - sensitivity);
      }
      break;

     case 2:
      localGaussThresh(b_I, outputSize, 0.6 + (1.0 - sensitivity), T);
      break;

     default:
      localGaussThresh(b_I, outputSize, 0.6 + (1.0 - sensitivity), T);
      break;
    }

    emxFree_real_T(&intA);
    emxFree_real_T(&paddedImage);
    emxFree_real_T(&b_I);
    i1 = T->size[0] * T->size[1];
    for (loop_ub = 0; loop_ub < i1; loop_ub++) {
      order1 = T->data[loop_ub];
      if (!(order1 < 1.0)) {
        order1 = 1.0;
      }

      if (!(order1 > 0.0)) {
        order1 = 0.0;
      }

      T->data[loop_ub] = order1;
    }
  }
}

/* End of code generation (adaptthresh.cpp) */
