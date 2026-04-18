#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <algorithm>
#include <vector>
#include "rapidcheck/gtest.h"
#include "sorting.h"
#include "test_helpers.h"


TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
    int arr[] = {1,5,6,7,8};
    int index = min_index_of_array(arr, 5);
    EXPECT_EQ(0, index);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
    int arr[] = {5,7,4,6,1};
    int index = min_index_of_array(arr, 5);
    EXPECT_EQ(4, index);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
    int arr[] = {5,7,1,6,9};
    int index = min_index_of_array(arr, 5);
    EXPECT_EQ(2, index);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
    int arr[] = {1,2,0,4,0};
    int index = min_index_of_array(arr, 5);
    EXPECT_EQ(2, index);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int arr[] = {1,2,0,4,0};
    int arr_og[] = {1,2,0,4,0};
    min_index_of_array(arr, 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], arr_og[i]);
    }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              ()) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    std::vector<int> values = *rc::gen::arbitrary<std::vector<int>>();
    int len = static_cast<int>(values.size());
    RC_PRE(len >= 1);
    int* arr = new int[len];
    copy_vector_to_array(values, arr);
    int mindex = min_index_of_array(arr, len);
    for (int i = 0; i < len; ++i) {
        RC_ASSERT(arr[i] >= arr[mindex]);
    }
    delete[] arr;
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              ()) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    std::vector<int> values = *rc::gen::arbitrary<std::vector<int>>();
    int len = static_cast<int>(values.size());
    RC_PRE(len >= 1);
    int* arr = new int[len];
    copy_vector_to_array(values, arr);
    min_index_of_array(arr, len);
    RC_ASSERT(elements_in_vector_and_array_are_same(values,arr));
    delete[] arr;
}
