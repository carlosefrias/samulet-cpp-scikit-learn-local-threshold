/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Threshold_rtwutil.cpp
 *
 * Code generation for function 'Threshold_rtwutil'
 *
 */
#include "pch.h"
/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Threshold_rtwutil.h"

/* Function Definitions */
double rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* End of code generation (Threshold_rtwutil.cpp) */
