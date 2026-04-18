# Google Test And Debugging Writeup

## Things I Thought To Test
1. already sorted array
2. all negative values
3. a mix of negative and positive values
4. all positive values
5. all the same value
6. an array with only one number
7. an empty array
8. an array with non-integer values
...

## Bugs

### Bug 1

### Location

lines: 1-3

```c++
int* temp = a;
a = b;
b = temp;
```

### How the bug was located

swap test

### Description

doesn't actually swap the values, it only swaps the values of the local copies

### Fix 

changed the swapped variables to pointers so that it points to the memory address and not a new local copy

```c++
int temp = *a;
  *a = *b;
  *b = temp;
```

### Bug 2

### Location

Line 3, 7

```c++
int min_index = 0;
  for (int i = 1; i < len; ++i) {
    if (ar[i] > ar[min_index]) {
      min_index = i;
    }
  }
  return ar[min_index];
```

### How the bug was located

Explain how you found the bug

### Description

instead of finding the index of the smallest value, it finds the largest value in the list and returns the largest value in the list

### Fix

I changed the greater than sign to a less than sign and then for the return, I just returned min_index

```c++
int min_index = 0;
  for (int i = 1; i < len; ++i) {
    if (ar[i] < ar[min_index]) {
      min_index = i;
    }
  }
  return min_index;
```

### Bug 3

### Location

line 1

```c++
int* copy = ar;
return copy;
}
```

### How the bug was located

Explain how you found the bug

### Description

instead of creating a whole new array, it creates an alias of the original array

### Fix

I traversed though each element in the reference list and set each element in the copy list to the element in the reference list

```c++
auto copy = new int[len];
  for (int i = 0; i < len; ++i) {
    copy[i] = ar[i];
  }
  return copy;
```
