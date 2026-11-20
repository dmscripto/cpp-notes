---
description: std::sort and std::ranges::sort, what they guarantee and how to sort by a key, with examples for C++17, C++20 and C++26.
---

# std::sort

<span class="std cpp98">C++98</span>

`std::sort` puts the elements of a range in ascending order, in place. By
default it compares with `<`; pass a comparator or, since C++20, a projection to
sort in another order or by a key.

It needs random-access iterators: `std::vector`, `std::array`, `std::deque`,
`std::string` and plain arrays. `std::list` has its own `list::sort()` member.
The sort is **not stable**: elements that compare equal can end up in any
order. Use `std::stable_sort` when that matters.

It does $O(N \log N)$ comparisons, guaranteed in the worst case since C++11.
Implementations use introsort; see [Sorting](../sorting/index.md) for how the
classic algorithms compare. Header: `<algorithm>`, plus `<execution>` for the
parallel overloads.

## Typical uses

- **Numbers or strings** in ascending order, or descending with
  `std::greater<>{}`.
- **Structs by a field** or several fields: a comparator lambda, or a
  projection in C++20.
- **Preparing data for other algorithms** that need sorted input:
  `std::unique` to drop duplicates, `std::binary_search` and `std::lower_bound`,
  `std::set_intersection`, `std::merge`.
- **Not for top-k.** If only the $k$ smallest elements matter,
  `std::partial_sort` or `std::nth_element` does less work.

## Examples

Every tab is a complete program compiled with that standard and checked in CI:
[code/algorithm/sort](https://github.com/dmscripto/cpp-notes/tree/main/code/algorithm/sort).

=== "C++17"

    ```cpp
    --8<-- "algorithm/sort/cpp17.cpp:example"
    ```

=== "C++20"

    ```cpp
    --8<-- "algorithm/sort/cpp20.cpp:example"
    ```

=== "C++26"

    ```cpp
    --8<-- "algorithm/sort/cpp26.cpp:example"
    ```

    The comments mark what came in C++23 and what in C++26.

    !!! note "Parallel `std::ranges::sort`"

        C++26 also adds `std::ranges::sort(std::execution::par, v)`
        ([P3179](https://wg21.link/P3179)). GCC 15's standard library does not
        have it yet, so it is not part of the tested example.

## What changed in each standard

| Standard                             | Change                                                                                        |
| ------------------------------------ | --------------------------------------------------------------------------------------------- |
| <span class="std cpp98">C++98</span> | `std::sort`, $O(N \log N)$ comparisons on average                                             |
| <span class="std cpp11">C++11</span> | $O(N \log N)$ comparisons required in the worst case too                                      |
| <span class="std cpp17">C++17</span> | Overloads that take an execution policy, such as `std::execution::par`                        |
| <span class="std cpp20">C++20</span> | `std::ranges::sort`: takes a whole range and a projection. `std::sort` becomes `constexpr`    |
| <span class="std cpp26">C++26</span> | `std::ranges::sort` takes an execution policy ([P3179](https://wg21.link/P3179)). `std::stable_sort` becomes `constexpr` too ([P2562](https://wg21.link/P2562)) |

## Pitfalls

- **The comparator must be a strict weak ordering.** `comp(a, a)` must be
  `false`, so `<=` is wrong. A broken comparator is undefined behaviour: in
  practice the sort can read past the end of the vector and crash.
- **NaN breaks the ordering of `double`.** Every comparison with NaN is
  `false`. Remove NaNs first, or compare with `std::strong_order` (C++20), which
  defines a total order on floating-point values.
- **Equal elements get shuffled.** Sorting by one key and then by another does
  not keep the first order. Sort once by a tuple of keys, or use
  `std::stable_sort` for the second pass.
- **Expensive keys.** A projection or comparator runs $O(N \log N)$ times. If
  the key is costly to compute, compute the keys once into a separate vector
  and sort both together (`std::views::zip` in C++23).

## See also

- [All algorithms by category](index.md)
- [`std::find`](find.md) for unsorted data
- `std::stable_sort`, `std::partial_sort`, `std::nth_element`, `std::is_sorted`
- [Bubble sort](../sorting/bubble-sort.md), step by step
- [`std::sort` on cppreference](https://en.cppreference.com/w/cpp/algorithm/sort)
