#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,2,3,4,5};
    int sorted_arr[] = {1,2,3,4,5};
    int len = 5;
    make_sorted(arr, len);
    for (int i = 0; i < len; ++i) {
      EXPECT_EQ(sorted_arr[i], arr[i]);
    }
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {5,4,3,2,1};
    int sorted_arr[] = {1,2,3,4,5};
    int len = 5;
    make_sorted(arr, len);
    for (int i = 0; i < len; ++i) {
        EXPECT_EQ(sorted_arr[i], arr[i]);
    }

}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {5,1,4,3,2};
    int sorted_arr[] = {1,2,3,4,5};
    int len = 5;
    make_sorted(arr, len);
    for (int i = 0; i < len; ++i) {
        EXPECT_EQ(sorted_arr[i], arr[i]);
    }
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {5,4,1,2,1};
    int sorted_arr[] = {1,1,2,4,5};
    int len = 5;
    make_sorted(arr, len);
    for (int i = 0; i < len; ++i) {
        EXPECT_EQ(sorted_arr[i], arr[i]);
    }
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = static_cast<int>(values.size());
    int* arr = new int[len];
    copy_vector_to_array(values, arr);
    make_sorted(arr, len);
    for (int i = 0; i < len-1; ++i) {
        RC_ASSERT(arr[i] <= arr[i+1]);
    }
    delete[] arr;
}
