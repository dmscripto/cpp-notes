/*
 * algo-viz: step-by-step visualizations of sorting algorithms.
 *
 * Put this into any Markdown page:
 *
 *   <div class="algo-viz" data-algo="bubble"></div>
 *
 * Attributes:
 *   data-algo    key in ALGORITHMS below (required): bubble, selection, insertion
 *   data-size    how many random values to sort, 4..16 (default 9)
 *   data-values  fixed comma-separated input, e.g. "5,1,4,2,8" (overrides data-size)
 *
 * Adding an algorithm = adding an entry to ALGORITHMS:
 *   code   the C++ lines shown under the bars
 *   steps  a generator that sorts `a` in place and yields one object per step:
 *            line    index into `code` to highlight (-1 for none)
 *            active  indices of the bars to highlight
 *            kind    "compare" | "swap" | "select" | "pass"
 *            note    text shown under the bars
 *          It may add indices to `done` (bars that reached their final place).
 */
(function () {
  "use strict";

  function swap(a, i, j) {
    const t = a[i];
    a[i] = a[j];
    a[j] = t;
  }

  const ALGORITHMS = {
    bubble: {
      code: [
        "for (int i = 0; i < n - 1; ++i)",
        "    for (int j = 0; j < n - 1 - i; ++j)",
        "        if (a[j] > a[j + 1])",
        "            std::swap(a[j], a[j + 1]);",
      ],
      *steps(a, done) {
        const n = a.length;
        for (let i = 0; i < n - 1; i++) {
          for (let j = 0; j < n - 1 - i; j++) {
            yield {
              line: 2, active: [j, j + 1], kind: "compare",
              note: `Compare a[${j}] = ${a[j]} and a[${j + 1}] = ${a[j + 1]}`,
            };
            if (a[j] > a[j + 1]) {
              swap(a, j, j + 1);
              yield {
                line: 3, active: [j, j + 1], kind: "swap",
                note: `${a[j + 1]} > ${a[j]}, swap them`,
              };
            }
          }
          done.add(n - 1 - i);
          yield {
            line: 0, active: [], kind: "pass",
            note: `Pass ${i + 1} is over: ${a[n - 1 - i]} has bubbled up to its final place`,
          };
        }
      },
    },

    selection: {
      code: [
        "for (int i = 0; i < n - 1; ++i) {",
        "    int min = i;",
        "    for (int j = i + 1; j < n; ++j)",
        "        if (a[j] < a[min])",
        "            min = j;",
        "    std::swap(a[i], a[min]);",
        "}",
      ],
      *steps(a, done) {
        const n = a.length;
        for (let i = 0; i < n - 1; i++) {
          let min = i;
          yield {
            line: 1, active: [i], kind: "select",
            note: `Start with a[${i}] = ${a[i]} as the minimum of the unsorted part`,
          };
          for (let j = i + 1; j < n; j++) {
            yield {
              line: 3, active: [j, min], kind: "compare",
              note: `Compare a[${j}] = ${a[j]} with the current minimum ${a[min]}`,
            };
            if (a[j] < a[min]) {
              min = j;
              yield { line: 4, active: [min], kind: "select", note: `New minimum: ${a[min]}` };
            }
          }
          done.add(i);
          if (min !== i) {
            swap(a, i, min);
            yield {
              line: 5, active: [i, min], kind: "swap",
              note: `Swap the minimum ${a[i]} into position ${i}`,
            };
          } else {
            yield { line: 5, active: [], kind: "pass", note: `${a[i]} is already in place` };
          }
        }
      },
    },

    insertion: {
      code: [
        "for (int i = 1; i < n; ++i)",
        "    for (int j = i; j > 0 && a[j - 1] > a[j]; --j)",
        "        std::swap(a[j - 1], a[j]);",
      ],
      *steps(a) {
        const n = a.length;
        for (let i = 1; i < n; i++) {
          for (let j = i; j > 0; j--) {
            yield {
              line: 1, active: [j - 1, j], kind: "compare",
              note: `Compare a[${j - 1}] = ${a[j - 1]} and a[${j}] = ${a[j]}`,
            };
            if (!(a[j - 1] > a[j])) break;
            swap(a, j - 1, j);
            yield {
              line: 2, active: [j - 1, j], kind: "swap",
              note: `Move ${a[j - 1]} one step to the left`,
            };
          }
          yield {
            line: 0, active: [], kind: "pass",
            note: `The first ${i + 1} elements are now sorted among themselves`,
          };
        }
      },
    },
  };

  const KIND_CLASS = {
    compare: "is-compare",
    swap: "is-swap",
    select: "is-select",
  };

  function el(tag, className, text) {
    const node = document.createElement(tag);
    if (className) node.className = className;
    if (text !== undefined) node.textContent = text;
    return node;
  }

  function randomValues(size) {
    return Array.from({ length: size }, () => 5 + Math.floor(Math.random() * 95));
  }

  function parseValues(attr) {
    if (!attr) return null;
    const values = attr.split(",").map((s) => Number(s.trim()));
    return values.length >= 2 && values.every((v) => Number.isFinite(v) && v > 0)
      ? values
      : null;
  }

  // Runs the generator to the end and records a snapshot of every step,
  // so the widget can go forwards and backwards freely.
  function recordSteps(algo, input) {
    const a = input.slice();
    const done = new Set();
    let comparisons = 0;
    let swaps = 0;
    const snapshot = (step) => ({
      line: step.line,
      active: step.active,
      kind: step.kind,
      note: step.note,
      values: a.slice(),
      done: new Set(done),
      comparisons,
      swaps,
    });

    const steps = [snapshot({ line: -1, active: [], kind: "start", note: "Press Step or Play" })];
    for (const step of algo.steps(a, done)) {
      if (step.kind === "compare") comparisons++;
      if (step.kind === "swap") swaps++;
      steps.push(snapshot(step));
    }
    a.forEach((_, i) => done.add(i));
    steps.push(snapshot({
      line: -1, active: [], kind: "end",
      note: `Sorted: ${comparisons} comparisons, ${swaps} swaps`,
    }));
    return steps;
  }

  class Viz {
    constructor(root) {
      this.root = root;
      this.timer = null;
      this.algo = ALGORITHMS[root.dataset.algo];
      if (!this.algo) {
        root.classList.add("algo-viz--error");
        root.textContent =
          `algo-viz: unknown algorithm "${root.dataset.algo}". ` +
          `Known: ${Object.keys(ALGORITHMS).join(", ")}.`;
        return;
      }
      this.fixedValues = parseValues(root.dataset.values);
      const size = parseInt(root.dataset.size, 10) || 9;
      this.size = Math.min(16, Math.max(4, size));
      this.build();
      this.load(this.fixedValues || randomValues(this.size));
    }

    build() {
      const root = this.root;
      root.replaceChildren();

      const stage = el("div", "algo-viz__stage");
      this.barsEl = el("div", "algo-viz__bars");
      this.barsEl.setAttribute("aria-hidden", "true");
      this.codeEl = el("div", "algo-viz__code");
      this.lineEls = this.algo.code.map((line) => {
        const node = el("div", "algo-viz__line", line);
        this.codeEl.appendChild(node);
        return node;
      });
      stage.append(this.barsEl, this.codeEl);

      this.statusEl = el("div", "algo-viz__status");
      this.statusEl.setAttribute("aria-live", "polite");

      const controls = el("div", "algo-viz__controls");
      this.backBtn = el("button", null, "◀ Back");
      this.stepBtn = el("button", null, "Step ▶");
      this.playBtn = el("button", null, "▶ Play");
      this.newBtn = el("button", null, this.fixedValues ? "↺ Restart" : "↻ Shuffle");
      [this.backBtn, this.stepBtn, this.playBtn, this.newBtn].forEach((b) => (b.type = "button"));

      const speedLabel = el("label", "algo-viz__speed", "Speed ");
      this.speedEl = el("input");
      this.speedEl.type = "range";
      this.speedEl.min = "1";
      this.speedEl.max = "10";
      this.speedEl.step = "1";
      this.speedEl.value = "5";
      speedLabel.appendChild(this.speedEl);

      this.countersEl = el("span", "algo-viz__counters");
      controls.append(this.backBtn, this.stepBtn, this.playBtn, this.newBtn, speedLabel, this.countersEl);

      const legend = el("div", "algo-viz__legend");
      [["is-compare", "compare"], ["is-swap", "swap"], ["is-select", "minimum"], ["is-done", "in final place"]]
        .filter(([cls]) => cls !== "is-select" || this.algo === ALGORITHMS.selection)
        .forEach(([cls, label]) => {
          const item = el("span");
          item.append(el("span", `algo-viz__swatch ${cls}`), document.createTextNode(label));
          legend.appendChild(item);
        });

      root.append(stage, this.statusEl, controls, legend);

      this.backBtn.addEventListener("click", () => { this.pause(); this.show(this.pos - 1); });
      this.stepBtn.addEventListener("click", () => { this.pause(); this.forward(); });
      this.playBtn.addEventListener("click", () => (this.timer ? this.pause() : this.play()));
      this.newBtn.addEventListener("click", () => {
        this.pause();
        this.load(this.fixedValues || randomValues(this.size));
      });
    }

    load(values) {
      this.steps = recordSteps(this.algo, values);
      this.max = Math.max(...values);
      this.barsEl.replaceChildren();
      this.bars = values.map(() => {
        const col = el("div", "algo-viz__col");
        const track = el("div", "algo-viz__track");
        const bar = el("div", "algo-viz__bar");
        const label = el("div", "algo-viz__label");
        track.appendChild(bar);
        col.append(track, label);
        this.barsEl.appendChild(col);
        return { bar, label };
      });
      this.show(0);
    }

    show(pos) {
      this.pos = Math.max(0, Math.min(this.steps.length - 1, pos));
      const s = this.steps[this.pos];
      s.values.forEach((v, i) => {
        const { bar, label } = this.bars[i];
        bar.style.height = `${Math.max(4, (v / this.max) * 100)}%`;
        label.textContent = v;
        const kindClass = s.active.includes(i) ? KIND_CLASS[s.kind] : null;
        bar.className = "algo-viz__bar " + (kindClass || (s.done.has(i) ? "is-done" : ""));
      });
      this.lineEls.forEach((node, i) => node.classList.toggle("is-active", i === s.line));
      this.statusEl.textContent = s.note;
      this.countersEl.textContent = `Comparisons: ${s.comparisons} · swaps: ${s.swaps}`;
    }

    forward() {
      if (this.pos >= this.steps.length - 1) return false;
      this.show(this.pos + 1);
      return true;
    }

    delay() {
      return 1100 - Number(this.speedEl.value) * 100;
    }

    play() {
      if (this.pos >= this.steps.length - 1) this.show(0);
      this.playBtn.textContent = "❚❚ Pause";
      const tick = () => {
        if (this.forward() && this.pos < this.steps.length - 1) {
          this.timer = setTimeout(tick, this.delay());
        } else {
          this.pause();
        }
      };
      this.timer = setTimeout(tick, 0);
    }

    pause() {
      clearTimeout(this.timer);
      this.timer = null;
      if (this.playBtn) this.playBtn.textContent = "▶ Play";
    }
  }

  // With instant navigation the page is swapped without a reload, so widgets
  // are (re)created on every `document$` emission and old timers are stopped.
  const instances = [];

  function initAll() {
    instances.splice(0).forEach((viz) => viz.pause());
    document.querySelectorAll(".algo-viz").forEach((root) => instances.push(new Viz(root)));
  }

  if (typeof document$ !== "undefined") {
    document$.subscribe(initAll);
  } else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", initAll);
  } else {
    initAll();
  }
})();
