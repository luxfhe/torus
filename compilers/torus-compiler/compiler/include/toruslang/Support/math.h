// Part of the Torus Compiler Project, under the BSD 3-Clause Clear
// License. See
// https://github.com/luxfhe/torus/blob/main/LICENSE.txt
// for license information.

#ifndef TORUSLANG_SUPPORT_MATH_H_
#define TORUSLANG_SUPPORT_MATH_H_

/// Calculates (T)ceil(log2f(v))
template <typename T> static T ceilLog2(const T v) {
  // TODO: Replace with some fancy bit twiddling hack
  T tmp = v;
  T log2 = 0;

  while (tmp >>= 1)
    log2++;

  // If more than MSB set, round to next highest power of 2
  if (v & ~((T)1 << log2))
    log2 += 1;

  return log2;
}

#endif
