---
description: Every algorithm of the C++ standard library by category, with the standard that introduced the classic and the ranges version.
---

# Algorithms library

The standard algorithms live in `<algorithm>`, the numeric ones in `<numeric>`
and the ones that work on raw memory in `<memory>`. Most come in two forms:

- **Classic**, `std::sort(v.begin(), v.end())`: takes a pair of iterators.
  Since C++17 most of them also accept an execution policy as the first
  argument, such as `std::execution::par` from `<execution>`.
- **Ranges**, `std::ranges::sort(v)` (C++20): takes a whole range, accepts a
  projection, checks its requirements with concepts and often returns more
  information. A few algorithms exist only in this form.

The tables show the standard that introduced each form. Names with a page here
are links; for the rest see [cppreference](https://en.cppreference.com/w/cpp/algorithm).

## What each standard added

| Standard                             | What it added                                                                                                                                       |
| ------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| <span class="std cpp98">C++98</span> | The original STL algorithms                                                                                                                         |
| <span class="std cpp11">C++11</span> | `all_of`, `any_of`, `none_of`, `find_if_not`, `copy_if`, `copy_n`, `move`, `shuffle`, `is_sorted`, `is_heap`, `minmax`, `is_permutation`, `iota` and more |
| <span class="std cpp14">C++14</span> | No new algorithms. `equal`, `mismatch` and `is_permutation` accept a full second range; `random_shuffle` is deprecated                              |
| <span class="std cpp17">C++17</span> | Execution policies; `for_each_n`, `sample`, `clamp`, `reduce`, the `*_scan` family, `uninitialized_move`, `destroy`; `random_shuffle` is removed    |
| <span class="std cpp20">C++20</span> | `std::ranges::` versions with projections; most algorithms become `constexpr`; `shift_left`, `shift_right`, `lexicographical_compare_three_way`     |
| <span class="std cpp23">C++23</span> | Ranges-only algorithms: `contains`, `starts_with`, `ends_with`, `find_last`, the `fold_*` family; `ranges::iota`, `ranges::shift_left`             |
| <span class="std cpp26">C++26</span> | Braced values like `find(v, {1, 2})`; `std::ranges::` overloads with execution policies; `constexpr stable_sort`; `ranges::generate_random`         |

<!-- The wrapper gives all tables below the same column widths. -->
<div class="std-index" markdown>

## Non-modifying

### Batch

| Algorithm    | What it does                              | `std::`                              | `std::ranges::`                      |
| ------------ | ----------------------------------------- | ------------------------------------ | ------------------------------------ |
| `for_each`   | Calls a function on every element         | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `for_each_n` | Calls a function on the first $n$ elements | <span class="std cpp17">C++17</span> | <span class="std cpp20">C++20</span> |

### Search

| Algorithm                                      | What it does                                            | `std::`                              | `std::ranges::`                      |
| ---------------------------------------------- | ------------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `all_of`, `any_of`, `none_of`                  | Checks a predicate for all, any or none of the elements | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `count`, `count_if`                            | Counts matching elements                                | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `mismatch`                                     | First position where two ranges differ                  | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `equal`                                        | Whether two ranges are equal element by element         | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| [`find`, `find_if`](find.md)                   | First element equal to a value or matching a predicate  | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| [`find_if_not`](find.md)                       | First element that does not match a predicate           | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `find_last`, `find_last_if`, `find_last_if_not` | Last matching element                                  | —                                    | <span class="std cpp23">C++23</span> |
| `find_end`                                     | Last occurrence of a subsequence                        | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `find_first_of`                                | First element equal to any of a set of values           | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `adjacent_find`                                | First pair of equal neighbours                          | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `search`                                       | First occurrence of a subsequence                       | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `search_n`                                     | First run of $n$ equal elements                         | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `contains`, `contains_subrange`                | Whether a value or a subsequence is in the range        | —                                    | <span class="std cpp23">C++23</span> |
| `starts_with`, `ends_with`                     | Whether a range begins or ends with another one         | —                                    | <span class="std cpp23">C++23</span> |

### Fold

The ranges replacement for `std::accumulate`.

| Algorithm                                    | What it does                                           | `std::` | `std::ranges::`                      |
| -------------------------------------------- | ------------------------------------------------------ | ------- | ------------------------------------ |
| `fold_left`, `fold_right`                    | Combines all elements with an initial value            | —       | <span class="std cpp23">C++23</span> |
| `fold_left_first`, `fold_right_last`         | Same, starting from the first or the last element      | —       | <span class="std cpp23">C++23</span> |
| `fold_left_with_iter`, `fold_left_first_with_iter` | Same as the left folds, also returns the end iterator | — | <span class="std cpp23">C++23</span> |

## Modifying

### Copy

| Algorithm       | What it does                                         | `std::`                              | `std::ranges::`                      |
| --------------- | ---------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `copy`          | Copies a range                                       | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `copy_if`       | Copies the elements that match a predicate           | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `copy_n`        | Copies $n$ elements                                  | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `copy_backward` | Copies from back to front, for overlapping ranges    | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `move`          | Moves elements to another range                      | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `move_backward` | Moves from back to front, for overlapping ranges     | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |

### Swap

| Algorithm     | What it does                                                | `std::`                              | `std::ranges::`                      |
| ------------- | ----------------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `swap`        | Swaps two values. In `<utility>` since C++11                | <span class="std cpp98">C++98</span> | —                                    |
| `swap_ranges` | Swaps the elements of two ranges                            | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `iter_swap`   | Swaps the elements that two iterators point to              | <span class="std cpp98">C++98</span> | —                                    |

### Transformation

| Algorithm                       | What it does                                         | `std::`                              | `std::ranges::`                      |
| ------------------------------- | ---------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `transform`                     | Applies a function and writes the results            | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `replace`, `replace_if`         | Replaces matching elements in place                  | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `replace_copy`, `replace_copy_if` | Copies a range, replacing matching elements        | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |

### Generation

| Algorithm    | What it does                                     | `std::`                              | `std::ranges::`                      |
| ------------ | ------------------------------------------------ | ------------------------------------ | ------------------------------------ |
| `fill`       | Assigns a value to every element                 | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `fill_n`     | Assigns a value to $n$ elements                  | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `generate`   | Assigns the results of successive function calls | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `generate_n` | Same for $n$ elements                            | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |

### Removing

| Algorithm                       | What it does                                                       | `std::`                              | `std::ranges::`                      |
| ------------------------------- | ------------------------------------------------------------------ | ------------------------------------ | ------------------------------------ |
| `remove`, `remove_if`           | Moves the kept elements to the front; pair it with `erase`         | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `remove_copy`, `remove_copy_if` | Copies all elements except the matching ones                       | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `unique`                        | Removes consecutive duplicates; pair it with `erase`               | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `unique_copy`                   | Copies a range without consecutive duplicates                      | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |

### Order-changing

| Algorithm                    | What it does                                               | `std::`                                                                         | `std::ranges::`                      |
| ---------------------------- | ---------------------------------------------------------- | ------------------------------------------------------------------------------- | ------------------------------------ |
| `reverse`                    | Reverses the order of elements                             | <span class="std cpp98">C++98</span>                                            | <span class="std cpp20">C++20</span> |
| `reverse_copy`               | Copies a range in reverse order                            | <span class="std cpp98">C++98</span>                                            | <span class="std cpp20">C++20</span> |
| `rotate`                     | Rotates elements so that a given one becomes the first     | <span class="std cpp98">C++98</span>                                            | <span class="std cpp20">C++20</span> |
| `rotate_copy`                | Copies a rotated range                                     | <span class="std cpp98">C++98</span>                                            | <span class="std cpp20">C++20</span> |
| `shift_left`, `shift_right`  | Shifts elements by $n$ positions                           | <span class="std cpp20">C++20</span>                                            | <span class="std cpp23">C++23</span> |
| `shuffle`                    | Random permutation with a given random generator           | <span class="std cpp11">C++11</span>                                            | <span class="std cpp20">C++20</span> |
| `random_shuffle`             | Random permutation; replaced by `shuffle`                  | <span class="std cpp98">C++98</span> <span class="std removed">removed in C++17</span> | —                              |

### Sampling

| Algorithm | What it does                     | `std::`                              | `std::ranges::`                      |
| --------- | -------------------------------- | ------------------------------------ | ------------------------------------ |
| `sample`  | Picks $n$ random elements        | <span class="std cpp17">C++17</span> | <span class="std cpp20">C++20</span> |

## Sorting and related

### Partitioning

| Algorithm          | What it does                                                     | `std::`                              | `std::ranges::`                      |
| ------------------ | ---------------------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `is_partitioned`   | Whether matching elements all come before the others             | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `partition`        | Moves matching elements to the front                             | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `partition_copy`   | Copies matching and other elements into two ranges               | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `stable_partition` | Like `partition`, keeps the relative order                       | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `partition_point`  | Finds the end of the first group in a partitioned range          | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |

### Sorting

| Algorithm             | What it does                                                   | `std::`                              | `std::ranges::`                      |
| --------------------- | -------------------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| [`sort`](sort.md)     | Sorts a range                                                  | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `stable_sort`         | Sorts and keeps the order of equal elements                    | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `partial_sort`        | Sorts only the first $k$ elements                              | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `partial_sort_copy`   | Copies the $k$ smallest elements in sorted order               | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `is_sorted`           | Whether a range is sorted                                      | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `is_sorted_until`     | Finds where the sorted prefix ends                             | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `nth_element`         | Puts the $n$-th element in place, smaller ones before it       | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |

### Binary search

On sorted (more precisely, partitioned) ranges, in $O(\log N)$.

| Algorithm       | What it does                                         | `std::`                              | `std::ranges::`                      |
| --------------- | ---------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `lower_bound`   | First element not less than a value                  | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `upper_bound`   | First element greater than a value                   | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `equal_range`   | The subrange of elements equal to a value            | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `binary_search` | Whether a value is there                             | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |

### Set operations

On sorted ranges.

| Algorithm                  | What it does                                        | `std::`                              | `std::ranges::`                      |
| -------------------------- | --------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `includes`                 | Whether one range contains all elements of another  | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `set_union`                | Elements that are in either range                   | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `set_intersection`         | Elements that are in both ranges                    | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `set_difference`           | Elements of the first range not in the second       | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `set_symmetric_difference` | Elements that are in exactly one of the ranges      | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |

### Merge

On sorted ranges.

| Algorithm       | What it does                                         | `std::`                              | `std::ranges::`                      |
| --------------- | ---------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `merge`         | Merges two sorted ranges into a third                | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `inplace_merge` | Merges two consecutive sorted parts of one range     | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |

### Heap

| Algorithm       | What it does                                         | `std::`                              | `std::ranges::`                      |
| --------------- | ---------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `make_heap`     | Turns a range into a max-heap                        | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `push_heap`     | Adds the last element to the heap                    | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `pop_heap`      | Moves the largest element to the end                 | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `sort_heap`     | Turns a heap into a sorted range                     | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `is_heap`       | Whether a range is a max-heap                        | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `is_heap_until` | Finds where the heap prefix ends                     | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |

### Min and max

| Algorithm                    | What it does                                     | `std::`                              | `std::ranges::`                      |
| ---------------------------- | ------------------------------------------------ | ------------------------------------ | ------------------------------------ |
| `min`, `max`                 | The smaller or the larger of values              | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `minmax`                     | Both at once                                     | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `min_element`, `max_element` | Iterator to the smallest or the largest element  | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `minmax_element`             | Both at once                                     | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `clamp`                      | Limits a value to a range                        | <span class="std cpp17">C++17</span> | <span class="std cpp20">C++20</span> |

### Comparison

| Algorithm                           | What it does                                         | `std::`                              | `std::ranges::`                      |
| ----------------------------------- | ---------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `lexicographical_compare`           | Whether one range is less than another, like strings | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `lexicographical_compare_three_way` | Same with `<=>`: less, equal or greater              | <span class="std cpp20">C++20</span> | —                                    |

### Permutation

| Algorithm                              | What it does                                        | `std::`                              | `std::ranges::`                      |
| -------------------------------------- | --------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `next_permutation`, `prev_permutation` | Next or previous permutation in lexicographic order | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `is_permutation`                       | Whether one range is a permutation of another       | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |

## Numeric

Header `<numeric>`. Except `iota`, these have no `std::ranges::` version; use
`std::ranges::fold_left` instead of `accumulate`.

| Algorithm                                              | What it does                                                    | `std::`                              | `std::ranges::`                      |
| ------------------------------------------------------ | --------------------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `iota`                                                 | Fills a range with increasing values                            | <span class="std cpp11">C++11</span> | <span class="std cpp23">C++23</span> |
| `accumulate`                                           | Sums elements, or folds them with a function, left to right     | <span class="std cpp98">C++98</span> | —                                    |
| `inner_product`                                        | Sum of products of two ranges                                   | <span class="std cpp98">C++98</span> | —                                    |
| `adjacent_difference`                                  | Differences between neighbours                                  | <span class="std cpp98">C++98</span> | —                                    |
| `partial_sum`                                          | Prefix sums                                                     | <span class="std cpp98">C++98</span> | —                                    |
| `reduce`                                               | Like `accumulate`, in any order, so it can run in parallel      | <span class="std cpp17">C++17</span> | —                                    |
| `transform_reduce`                                     | Transforms, then reduces                                        | <span class="std cpp17">C++17</span> | —                                    |
| `inclusive_scan`, `exclusive_scan`                     | Prefix sums that can run in parallel                            | <span class="std cpp17">C++17</span> | —                                    |
| `transform_inclusive_scan`, `transform_exclusive_scan` | Transforms, then scans                                          | <span class="std cpp17">C++17</span> | —                                    |

## Uninitialized memory

Header `<memory>`. For code that manages raw storage itself, such as a
container.

| Algorithm                                                            | What it does                                        | `std::`                              | `std::ranges::`                      |
| -------------------------------------------------------------------- | --------------------------------------------------- | ------------------------------------ | ------------------------------------ |
| `construct_at`                                                       | Creates an object at an address                     | <span class="std cpp20">C++20</span> | <span class="std cpp20">C++20</span> |
| `destroy_at`                                                         | Destroys an object at an address                    | <span class="std cpp17">C++17</span> | <span class="std cpp20">C++20</span> |
| `destroy`, `destroy_n`                                               | Destroys a range of objects                         | <span class="std cpp17">C++17</span> | <span class="std cpp20">C++20</span> |
| `uninitialized_copy`                                                 | Copies a range into raw memory                      | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `uninitialized_copy_n`                                               | Copies $n$ elements into raw memory                 | <span class="std cpp11">C++11</span> | <span class="std cpp20">C++20</span> |
| `uninitialized_fill`, `uninitialized_fill_n`                         | Fills raw memory with copies of a value             | <span class="std cpp98">C++98</span> | <span class="std cpp20">C++20</span> |
| `uninitialized_move`, `uninitialized_move_n`                         | Moves a range into raw memory                       | <span class="std cpp17">C++17</span> | <span class="std cpp20">C++20</span> |
| `uninitialized_default_construct`, `uninitialized_default_construct_n` | Default-initializes objects in raw memory         | <span class="std cpp17">C++17</span> | <span class="std cpp20">C++20</span> |
| `uninitialized_value_construct`, `uninitialized_value_construct_n`   | Value-initializes objects in raw memory             | <span class="std cpp17">C++17</span> | <span class="std cpp20">C++20</span> |

## Random numbers

Header `<random>`.

| Algorithm         | What it does                                               | `std::` | `std::ranges::`                      |
| ----------------- | ---------------------------------------------------------- | ------- | ------------------------------------ |
| `generate_random` | Fills a range with random numbers, possibly in one batch   | —       | <span class="std cpp26">C++26</span> |

## C library

Header `<cstdlib>`. Prefer `std::sort` and `std::binary_search`: they are type
safe and usually faster.

| Algorithm | What it does                         | `std::`                              | `std::ranges::` |
| --------- | ------------------------------------ | ------------------------------------ | --------------- |
| `qsort`   | Sorts an array of any type           | <span class="std cpp98">C++98</span> | —               |
| `bsearch` | Binary search in a sorted array      | <span class="std cpp98">C++98</span> | —               |

</div>
