# C++ notes

Personal notes on C++ and algorithms, built with [Zensical](https://zensical.org)
(the successor of Material for MkDocs) and published to GitHub Pages.

Live site: <https://dmscripto.github.io/cpp-notes/>

## Project layout

```text
docs/                    site pages (Markdown)
  algorithms-library/      one page per standard algorithm + overview
  javascripts/algo-viz.js  step-by-step algorithm visualizations
  javascripts/katex.js     math rendering
  stylesheets/algo-viz.css widget styles
  stylesheets/std.css      C++ standard badges and overview tables
code/                    C++ code shown on the site: *_test.cpp tests and
                         cppNN.cpp examples (code/algorithm/<name>/)
scripts/test-code.sh     compiles and runs all tests and examples
templates/               templates for new pages (not published)
zensical.toml            site configuration
.github/workflows/docs.yml  CI: test C++ code, then build and deploy the site
```

## Preview locally (Windows, PowerShell)

One-time setup:

```powershell
python -m venv .venv
.venv\Scripts\python -m pip install -r requirements.txt
```

Run the preview server with live reload, then open <http://localhost:8000/cpp-notes/>:

```powershell
.venv\Scripts\zensical serve
```

## Write a new article

1. Copy `templates/article.md` to `docs/<section>/<name>.md`.
2. Put the C++ code into `code/<section>/<name>.hpp`. Wrap the part to show in
   `// --8<-- [start:main]` and `// --8<-- [end:main]` and include it in the page:

   ````markdown
   ```cpp
   --8<-- "<section>/<name>.hpp:main"
   ```
   ````

3. Add tests in `code/<section>/<name>_test.cpp` (a `main` that returns non-zero on failure).

The navigation is generated from the folder structure, so new pages show up
automatically. A folder's `index.md` becomes the section's overview page, and
the folder name becomes the section title (`algorithms-library` →
"Algorithms library").

## Add a page to the algorithms library

1. Copy `templates/algorithm.md` to `docs/algorithms-library/<name>.md`.
2. Write the examples as complete programs in `code/algorithm/<name>/cpp17.cpp`,
   `cpp20.cpp` and `cpp26.cpp`. Wrap the part to show in
   `// --8<-- [start:example]` and `// --8<-- [end:example]` (it may be inside
   `main`; the indentation is removed) and check the results with `assert`
   after it. Each file is compiled with the standard in its name.
3. Turn the algorithm's name into a link in the table on
   `docs/algorithms-library/index.md`.

Mark standards with badges: `<span class="std cpp20">C++20</span>` (classes
`cpp98`, `cpp11`, `cpp14`, `cpp17`, `cpp20`, `cpp23`, `cpp26`).

## Add a visualization

Put a widget anywhere in a page:

```html
<div class="algo-viz" data-algo="bubble"></div>
<div class="algo-viz" data-algo="insertion" data-values="5,1,4,2,8"></div>
```

Available algorithms: `bubble`, `selection`, `insertion`. To add one, add an
entry to `ALGORITHMS` in `docs/javascripts/algo-viz.js`: the C++ lines to show
and a generator that sorts the array and yields one step at a time. The comment
at the top of the file describes the format.

## Test the C++ code

```powershell
bash scripts/test-code.sh
bash scripts/test-code.sh code/algorithm/find   # only some paths
```

Uses `g++` by default; set `CXX=clang++` to use Clang. The C++26 examples need
GCC 15 or newer. CI runs the same script on Ubuntu 26.04 (g++ 15) with
AddressSanitizer and UndefinedBehaviorSanitizer enabled.

## Publish to GitHub Pages

1. Create a repository named `cpp-notes` on GitHub and push this folder to `main`.
2. In the repository, open **Settings → Pages** and set **Source** to **GitHub Actions**.
3. Every push to `main` runs the workflow: it tests the C++ code, builds the site
   and deploys it. Pull requests only run the checks.

If the repository or account name differs, update `site_url` and `repo_url` in
`zensical.toml`.
