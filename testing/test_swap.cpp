#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = 1;
    int b = 2;
    swap(&a, &b);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
  int arr[] = {1,2,3,4,5};
  swap(&arr[0], &arr[1]);
  EXPECT_EQ(arr[0], 2);
  EXPECT_EQ(arr[1], 1);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
  int a = a_start;
  int b = b_start;
  swap(&a, &b);
  RC_ASSERT(a == b_start);
  RC_ASSERT(b == a_start);
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
  int len = static_cast<int>(values.size());
  RC_PRE(len>=2);
  int* arr = new int[len];
  copy_vector_to_array(values, arr);
  int a = arr[0];
  int b = arr[1];
  swap(&arr[0], &arr[1]);
  RC_ASSERT(arr[0] == b);
  RC_ASSERT(arr[1] == a);
  delete[] arr;
}
