---
description: std::find and std::ranges::find, the linear search of the standard library, with examples for C++17, C++20 and C++26.
---

# std::find

<span class="std cpp98">C++98</span>

`std::find` walks a range from the front and returns an iterator to the first
element equal to a value, or the end of the range if there is none. `find_if`
does the same with a predicate, and `find_if_not` with a negated one.

It is a plain linear search: up to $N$ comparisons and no requirements on the
order of elements. Header: `<algorithm>`.

## Typical uses

- **Is the value there?** Compare the result with `end()`. C++23 adds
  `std::ranges::contains` for exactly this question.
- **Where is it?** The iterator is the position: `it - v.begin()` gives the
  index, and `std::distance` does the same for lists.
- **Find and change.** Modify the element through the iterator, or pass the
  iterator on to `erase`, `insert` and other functions that take a position.
- **Search by a field** of a struct: `find_if` with a lambda, or in C++20
  `std::ranges::find` with a projection such as `&User::name`.

## Examples

Every tab is a complete program compiled with that standard and checked in CI:
[code/algorithm/find](https://github.com/dmscripto/cpp-notes/tree/main/code/algorithm/find).

=== "C++17"

    ```cpp
    --8<-- "algorithm/find/cpp17.cpp:example"
    ```

=== "C++20"

    ```cpp
    --8<-- "algorithm/find/cpp20.cpp:example"
    ```

=== "C++26"

    ```cpp
    --8<-- "algorithm/find/cpp26.cpp:example"
    ```

    The comments mark what came in C++23 and what in C++26.

## Pitfalls

- **Not checking for `end()`.** Dereferencing the end iterator is undefined
  behaviour, and it is what you get when nothing is found.
- **Searching where a faster lookup exists.** `find` is always $O(N)$. A sorted
  vector has `std::binary_search` and `std::lower_bound` in $O(\log N)$;
  `std::set` and `std::map` have a `find` member in $O(\log N)$, the unordered
  containers in $O(1)$ on average.
- **A temporary range.** `std::ranges::find(make_vector(), 4)` returns
  `std::ranges::dangling` instead of an iterator, because the vector dies at the
  end of the statement. Using the result does not compile: store the vector in
  a variable first.
- **`std::string::find` is a different function.** It searches for a character
  or a substring and returns an index, or `std::string::npos` if there is none.
- **Floating-point values.** `find` compares with `==`. For computed values
  use `find_if` with a tolerance.

## See also

- [All algorithms by category](index.md)
- [`std::sort`](sort.md): sort first, then search in $O(\log N)$ with
  `std::lower_bound` or `std::binary_search`.
- `std::find_first_of`, `std::adjacent_find`, `std::search`: other kinds of
  search.
- [`std::find` on cppreference](https://en.cppreference.com/w/cpp/algorithm/find)
