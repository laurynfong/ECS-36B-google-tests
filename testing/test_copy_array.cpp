#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int arr[] = {1,2,3};
  int len = 3;
  int* copy = copy_array(arr, len);
  for (int i = 0; i < len; ++i) {
    EXPECT_EQ(arr[i], copy[i]);
  }
  delete[] copy;
}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int arr_og[] = {1,2,3};
  int arr[] = {1,2,3};
  int len = 3;
  copy_array(arr, len);
  for (int i = 0; i < len; ++i) {
    EXPECT_EQ(arr[i], arr_og[i]);
  }
}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int arr[] = {1,2,3};
  int len = 3;
  EXPECT_NE(copy_array(arr, len), arr);
}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int len = static_cast<int>(values.size());
  int* arr = new int[len];
  copy_vector_to_array(values, arr);
  int* copy_arr = copy_array(arr, len);
  for (int i = 0; i < len; ++i) {
    RC_ASSERT(arr[i] == copy_arr[i]);
  }
  delete[] arr;
  delete[] copy_arr;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>& values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int len = static_cast<int>(values.size());
  int* arr = new int[len];
  copy_vector_to_array(values, arr);
  copy_array(arr, len);
  RC_ASSERT(elements_in_vector_and_array_are_same(values, arr));
  delete[] arr;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>& values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */
  int len = static_cast<int>(values.size());
  int* arr = new int[len];
  copy_vector_to_array(values, arr);
  int* copy_arr = copy_array(arr, len);
  RC_ASSERT_FALSE(copy_arr == arr);
  delete[] arr;
  delete[] copy_arr;
}



