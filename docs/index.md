---
description: Personal notes on C++ and algorithms.
---

# C++ notes

Notes on C++ and algorithms: how things work, with code that compiles and
visualizations you can step through.

## Sections

- [Sorting](sorting/index.md): classic sorting algorithms, from bubble sort to
  `std::sort`. Start with [bubble sort](sorting/bubble-sort.md).
- [Algorithms library](algorithms-library/index.md): every standard algorithm by
  category and the standard it came in, with pages for
  [`std::find`](algorithms-library/find.md) and [`std::sort`](algorithms-library/sort.md).

## How a page is built

| Part           | Where it lives                    | Notes                                              |
| -------------- | --------------------------------- | -------------------------------------------------- |
| Text           | `docs/**/*.md`                    | Markdown with math, diagrams, tabs and admonitions |
| C++ code       | `code/**/*.hpp`, `*_test.cpp`     | Included into pages, compiled and tested in CI     |
| Examples       | `code/**/cpp17.cpp`, `cpp20.cpp`… | Each compiled with the standard in its name        |
| Visualizations | `docs/javascripts/algo-viz.js`    | `<div class="algo-viz" data-algo="bubble"></div>`  |
| Standard tags  | `docs/stylesheets/std.css`        | `<span class="std cpp20">C++20</span>`             |

Templates for new pages are in `templates/`: `article.md` for articles,
`algorithm.md` for the algorithms library.
