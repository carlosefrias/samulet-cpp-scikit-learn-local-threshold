/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sqrt.cpp
 *
 * Code generation for function 'sqrt'
 *
 */
#include "pch.h"
/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "Threshold.h"
#include "sqrt.h"

/* Function Definitions */
void b_sqrt(double *x)
{
  *x = std::sqrt(*x);
}

/* End of code generation (sqrt.cpp) */
