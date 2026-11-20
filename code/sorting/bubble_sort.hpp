#pragma once

// The --8<-- [start:name] / [end:name] markers below let the docs include
// one section of this file at a time (see docs/sorting/bubble-sort.md).

// --8<-- [start:simple]
#include <cstddef>
#include <utility>
#include <vector>

void bubble_sort(std::vector<int>& a) {
    const std::size_t n = a.size();
    for (std::size_t i = 0; i + 1 < n; ++i)
        for (std::size_t j = 0; j + 1 < n - i; ++j)
            if (a[j] > a[j + 1])
                std::swap(a[j], a[j + 1]);
}
// --8<-- [end:simple]

// --8<-- [start:generic]
#include <algorithm>   // std::iter_swap
#include <functional>  // std::less
#include <iterator>    // std::random_access_iterator

template <std::random_access_iterator It, class Compare = std::less<>>
void bubble_sort(It first, It last, Compare comp = {}) {
    // [first, end) is the unsorted part; everything after it is in place.
    for (auto end = last; end - first > 1; --end) {
        bool swapped = false;
        for (auto it = first; it + 1 != end; ++it) {
            if (comp(*(it + 1), *it)) {  // strict "less": keeps the sort stable
                std::iter_swap(it, it + 1);
                swapped = true;
            }
        }
        if (!swapped)
            break;  // no swaps in a full pass: already sorted, O(n) best case
    }
}
// --8<-- [end:generic]
