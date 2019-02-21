/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Threshold.cpp
 *
 * Code generation for function 'Threshold'
 *
 */
#include "pch.h"
/* Include files */
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "adaptthresh.h"

/* Function Definitions */
void Threshold(const emxArray_uint16_T *X, double sensitivity, signed char mode,
               emxArray_real_T *T)
{
  int thresMode_size[2];
  char thresMode_data[8];
  int i0;
  static const char cv0[6] = { 'm', 'e', 'd', 'i', 'a', 'n' };

  static const char cv1[8] = { 'g', 'a', 'u', 's', 's', 'i', 'a', 'n' };

  if (mode == 0) {
    thresMode_size[0] = 1;
    thresMode_size[1] = 4;
    thresMode_data[0] = 'm';
    thresMode_data[1] = 'e';
    thresMode_data[2] = 'a';
    thresMode_data[3] = 'n';
  } else if (mode == 1) {
    thresMode_size[0] = 1;
    thresMode_size[1] = 8;
    for (i0 = 0; i0 < 8; i0++) {
      thresMode_data[i0] = cv1[i0];
    }
  } else {
    thresMode_size[0] = 1;
    thresMode_size[1] = 6;
    for (i0 = 0; i0 < 6; i0++) {
      thresMode_data[i0] = cv0[i0];
    }
  }

  adaptthresh(X, sensitivity, thresMode_data, thresMode_size, T);
}

/* End of code generation (Threshold.cpp) */
