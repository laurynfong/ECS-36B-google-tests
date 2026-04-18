#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int arr[] = {1,2,3,4,5};
  int* sorted = get_sorted(arr,5);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr[i], sorted[i]);
  }
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {5,4,3,2,1};
    int arr_sorted[] = {1,2,3,4,5};
    int* sorted = get_sorted(arr,5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr_sorted[i], sorted[i]);
    }
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,5,3,8,2};
    int arr_sorted[] = {1,2,3,5,8};
    int* sorted = get_sorted(arr,5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr_sorted[i], sorted[i]);
    }

}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,8,3,8,2};
    int arr_sorted[] = {1,2,3,8,8};
    int* sorted = get_sorted(arr,5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr_sorted[i], sorted[i]);
    }


}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,5,3,8,2};
    int arr_og[] = {1,5,3,8,2};
    get_sorted(arr,5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], arr_og[i]);
    }


}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,5,3,8,2};
    int* copy = get_sorted(arr,5);
    EXPECT_NE(copy, arr);
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    int len = static_cast<int>(values.size());
    int* arr = new int[len];
    copy_vector_to_array(values, arr);
    int* copy = get_sorted(arr, len);
    for (int i = 0; i < len-1; i++) {
        RC_ASSERT(copy[i] <= copy[i+1]);
    }
    delete [] arr;

}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = static_cast<int>(values.size());
    int* arr = new int[len];
    int* arr_og = new int[len];
    copy_vector_to_array(values, arr);
    for (int i = 0; i < len; i++) {
        arr_og[i] = arr[i];
    }
    get_sorted(arr,len);
    for (int i = 0; i< len; i++) {
        RC_ASSERT(arr[i] == arr_og[i]);
    }

    delete[] arr;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = static_cast<int>(values.size());
    int* arr = new int[len];
    copy_vector_to_array(values, arr);
    int* copy = get_sorted(arr, len);
    RC_ASSERT_FALSE(copy == arr);
    delete[] arr;
}











