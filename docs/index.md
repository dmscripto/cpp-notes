---
description: Personal notes on C++ and algorithms.
---

# C++ notes

Notes on C++ and algorithms: how things work, with code that compiles and
visualizations you can step through.

## Sections

- [Sorting](sorting/index.md): classic sorting algorithms, from bubble sort to
  `std::sort`. Start with [bubble sort](sorting/bubble-sort.md).

## How a page is built

| Part           | Where it lives                    | Notes                                              |
| -------------- | --------------------------------- | -------------------------------------------------- |
| Text           | `docs/**/*.md`                    | Markdown with math, diagrams, tabs and admonitions |
| C++ code       | `code/**/*.hpp`, `*_test.cpp`     | Included into pages, compiled and tested in CI     |
| Visualizations | `docs/javascripts/algo-viz.js`    | `<div class="algo-viz" data-algo="bubble"></div>`  |

A template for new articles is in `templates/article.md`.
