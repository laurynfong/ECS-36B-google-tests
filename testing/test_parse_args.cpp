#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    return rc::gen::container<std::string>(rc::gen::inRange<char>('a', 'z' + 1));
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
  std::vector<std::string> strs;
  strs.reserve(numbers.size());

  for (int n : numbers) {
    strs.push_back(std::to_string(n));
  }

  return strs;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
  const char* argv[] = {"./a.out", "1", "2", "3", "4", "5"};
  int len;
  int* arr = nullptr;
  parse_args(6, argv, &arr, &len);
  EXPECT_EQ(len, 5);
  for (int i = 0; i < len; i++) {
    EXPECT_EQ(arr[i], i+1);
  }
  free(arr);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
  int len;
  const char* argv[] = {"./a.out"};
  int* arr = nullptr;
  parse_args(1, argv, &arr, &len);
  EXPECT_EQ(len, 0);
  EXPECT_EQ(arr, nullptr);
  free(arr);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              ()
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */

  std::vector<int> values = *rc::gen::arbitrary<std::vector<int>>();
  RC_PRE(static_cast<int>(values.size()) > 0);

  RC_PRE(static_cast<int>(values.size())>0);
  std::vector<std::string> strs = vector_of_ints_to_vector_of_strings(values);
  strs.insert(strs.begin(),"./a.out");

  const char** arr = new const char*[strs.size()];
  for (size_t i = 0; i < strs.size(); i++) {
    arr[i] = strs[i].c_str();
  }

  int* ar_out = nullptr;
  int len_out;
  int argc = static_cast<int>(strs.size());
  parse_args(argc, arr, &ar_out, &len_out);
  RC_ASSERT(len_out == (argc-1));
  for (int i = 0; i < len_out; i++) {
    RC_ASSERT(ar_out[i] == values.at(i));
  }
  free(ar_out);
  delete[] arr;
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
  int len;
  const char* argv[] = {"./a.out"};
  int* arr = nullptr;
  parse_args(1, argv, &arr, &len);
  RC_ASSERT(len == 0);
  RC_ASSERT(arr == nullptr);
  free(arr);
};
