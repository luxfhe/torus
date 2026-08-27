#include <gtest/gtest.h>

#include "toruslang/Runtime/wrappers.h"

namespace {

TEST(WrappersDeathTest, bad_alloc) {
  ASSERT_DEATH(
      { torus_checked_malloc(SIZE_MAX); },
      "bad alloc: nullptr while calling "
      "malloc\\(17179869183 GB\\).*Backtrace:.*");
}

} // namespace
