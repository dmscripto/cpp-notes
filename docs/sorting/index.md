---
description: Overview of classic sorting algorithms and their complexity.
---

# Sorting

| Algorithm                     | Best             | Average          | Worst              | Extra memory  | Stable |
| ----------------------------- | ---------------- | ---------------- | ------------------ | ------------- | ------ |
| [Bubble sort](bubble-sort.md) | $O(n)$[^early]   | $O(n^2)$         | $O(n^2)$           | $O(1)$        | yes    |
| Selection sort                | $O(n^2)$         | $O(n^2)$         | $O(n^2)$           | $O(1)$        | no     |
| Insertion sort                | $O(n)$           | $O(n^2)$         | $O(n^2)$           | $O(1)$        | yes    |
| Merge sort                    | $O(n \log n)$    | $O(n \log n)$    | $O(n \log n)$      | $O(n)$        | yes    |
| Quicksort                     | $O(n \log n)$    | $O(n \log n)$    | $O(n^2)$           | $O(\log n)$   | no     |
| Heapsort                      | $O(n \log n)$    | $O(n \log n)$    | $O(n \log n)$      | $O(1)$        | no     |
| `std::sort`                   |                  | $O(n \log n)$    | $O(n \log n)$      |               | no     |
| `std::stable_sort`            |                  | $O(n \log n)$    | $O(n \log^2 n)$[^stable] |         | yes    |

[^early]: Only with the early exit: stop when a whole pass made no swaps.
[^stable]: $O(n \log n)$ when enough extra memory is available, $O(n \log^2 n)$ otherwise.

`std::sort` is usually an *introsort*: quicksort that switches to heapsort when
the recursion gets too deep, and insertion sort for small ranges. Since C++11
the standard guarantees $O(n \log n)$ comparisons in the worst case.

## Which one to use

```mermaid
flowchart TD
    stable{"Must equal elements keep their order?"}
    stable -- yes --> ss["std::stable_sort"]
    stable -- no --> part{"Need only the k smallest elements?"}
    part -- yes --> ps["std::partial_sort or std::nth_element"]
    part -- no --> s["std::sort"]
```

## Same input, three quadratic sorts

All three widgets below sort the same array. Compare how many comparisons and
swaps each one needs.

### Bubble sort

<div class="algo-viz" data-algo="bubble" data-values="7,3,9,1,6,2,8,4,5"></div>

### Selection sort

Finds the minimum of the unsorted part and swaps it to the front: at most
$n - 1$ swaps, but always $\frac{n(n-1)}{2}$ comparisons.

<div class="algo-viz" data-algo="selection" data-values="7,3,9,1,6,2,8,4,5"></div>

### Insertion sort

Takes the next element and moves it left until it is in place inside the sorted
prefix. On nearly sorted input it does almost no work.

<div class="algo-viz" data-algo="insertion" data-values="7,3,9,1,6,2,8,4,5"></div>
