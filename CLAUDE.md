# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

A personal static site about C++ and algorithms, built with Zensical 0.1.3
(the successor of Material for MkDocs; config is `zensical.toml`, not `mkdocs.yml`)
and deployed to GitHub Pages: https://dmscripto.github.io/cpp-notes/

## Commands

Run everything from the repository root: snippet paths in `zensical.toml`
resolve relative to the current directory, so running Zensical elsewhere fails
with `SnippetMissingError`.

```powershell
python -m venv .venv
.venv\Scripts\python -m pip install -r requirements.txt   # one-time setup
.venv\Scripts\zensical serve --dev-addr localhost:8011     # live preview
.venv\Scripts\zensical build --clean                       # build into site/
bash scripts/test-code.sh                                  # all C++ tests and examples
bash scripts/test-code.sh code/algorithm/find              # only some paths
```

- Port 8000 (the default) may be unavailable on this machine, hence 8011,
  which is also what `.claude/launch.json` uses. The site is served under
  `/cpp-notes/`; `/` redirects there.
- The script compiles `*_test.cpp` as C++20 and `cppNN.cpp` with
  `-std=c++NN`, with `-Wall -Wextra -Wpedantic -Werror`.
- Use g++ (15.2 here). The C++26 examples need libstdc++ 15. Plain `clang++`
  on this machine targets the MSVC STL, which lacks them, so
  `CXX=clang++ bash scripts/test-code.sh` fails on `cpp26.cpp`; clang works
  with `--target=x86_64-w64-mingw32`. `.clangd` sets that target and the
  per-file standard for the editor.
- Sanitizers are not available with MinGW, so they only run in CI (Ubuntu
  26.04 with g++ 15, ASan + UBSan). The CI runner is pinned to `ubuntu-26.04`
  for that compiler.

## How the pieces fit together

**C++ code lives in `code/`, not in the pages.** Articles in `docs/` pull it in
with `pymdownx.snippets` (`base_path = code`, `check_paths = true`, so a wrong
path fails the build). Headers mark named sections with
`// --8<-- [start:name]` / `// --8<-- [end:name]`, and a page includes one with
`--8<-- "sorting/bubble_sort.hpp:simple"` inside a `cpp` fence. Each header has a
`*_test.cpp` next to it: a plain `main` that returns non-zero on failure (no test
framework). Articles show a simple version and a generic C++20 version
(iterators + concepts) in content tabs, as `docs/sorting/bubble-sort.md` does.
`compile_flags.txt` gives clangd `-std=c++20 -Icode`; `.clangd` adds the rest.

**The algorithms library section** (`docs/algorithms-library/`) has one page per
standard algorithm and an overview `index.md` listing every algorithm.
- **Examples.** Each page shows examples in "C++17" / "C++20" / "C++26" tabs. The
  tabs are cumulative, so the C++26 tab also shows C++23 features, marked in
  comments. The same tab labels on every page are linked by
  `content.tabs.link`, so the reader's choice carries across pages.
- **Example files.** Every tab is `code/algorithm/<name>/cppNN.cpp`, a complete
  program. Its `example` section sits inside `main`; `dedent_subsections`
  strips the indentation. The asserts after the section check the result
  comments in the example.
- **Untested code.** A feature no standard library ships yet, such as P3179
  parallel `std::ranges::sort`, goes in a note in prose, never in tested code.
- **Badges.** Standards are marked with `<span class="std cpp20">C++20</span>`
  (`docs/stylesheets/std.css`).
- **Overview tables** sit inside `<div class="std-index" markdown>`, which gives
  them aligned columns. Algorithms that have a page are links there. Adding a
  page means: copy `templates/algorithm.md`, add the three example files, and
  link the name in the overview.

**CI gates the deploy on the tests.** `.github/workflows/docs.yml` runs
`test-code` and then `deploy` (build + upload to Pages) on pushes to `main`; pull
requests only run the tests. Re-running a failed `deploy` job fails with
"No artifacts named github-pages"; start a fresh run instead with
`gh workflow run docs.yml --ref main`.

**Navigation comes from the folder structure.** There is no `nav` in
`zensical.toml`; a folder's `index.md` is its section overview. The section title
in the nav comes from the folder name, not from the index page's H1:
`algorithms-library` becomes "Algorithms library". New articles start from
`templates/article.md`, which sits outside `docs/` so it is not published.

**Instant navigation swaps pages without a reload.** Custom scripts must
(re)initialize through `document$.subscribe(...)`, not `DOMContentLoaded`. Both
`docs/javascripts/katex.js` and `algo-viz.js` do this. `algo-viz.js` also stops
timers of widgets from the previous page.

**Math and diagrams.** `pymdownx.arithmatex` (generic mode) turns `$...$` into
`\(...\)`, which KaTeX (from unpkg, pinned to 0.16.22) renders client-side.
Mermaid fences are rendered by the theme itself. Prefer compact `flowchart LR`
layouts, because a tall `TD` chart takes over the page.

## Visualization widget (`docs/javascripts/algo-viz.js`)

Pages embed `<div class="algo-viz" data-algo="bubble" data-values="..."></div>`
(`md_in_html` is enabled). Each `ALGORITHMS` entry has:

- `code`: the C++ lines to display. They are hand-written in JS, not taken from
  `code/`, so keep them in sync with the article by hand.
- `*steps(a, done)`: a generator that re-implements the algorithm in JS and
  yields `{line, active, kind, note}`.

`recordSteps` runs the generator to the end up front and snapshots every step,
which is what makes Back work. The comparison and swap counters count steps
whose `kind` is `compare` or `swap`. So a generator must yield exactly one
`compare` per real comparison and one `swap` per real swap, or the counters will
not match the article's numbers.

Styling is in `docs/stylesheets/algo-viz.css`. The colors are mid-tones that work
on both the light (`default`) and dark (`slate`) schemes. Bars are absolutely
positioned inside a relative `__track`, because percentage heights on flex
children get squashed. The code panel sits under the bars at full width so long
lines fit.

## Gotchas

- GitHub Pages serves CSS/JS with `max-age=600`, so after a deploy a browser may
  show old styles for up to 10 minutes. To verify a deploy, fetch the file with
  `cache: 'no-store'` or add a query string.
- `core.autocrlf` is on; `.gitattributes` keeps `*.sh` as LF so bash in CI can
  run them.
- The theme requests `api.github.com/.../releases/latest` and gets 404, because
  the repo has no releases. This is harmless.
