// Renders math written as $...$ or $$...$$ in Markdown.
// pymdownx.arithmatex (generic mode) turns those into \( \) and \[ \],
// so only these delimiters are needed here. `document$` re-runs the
// rendering after every instant-navigation page change.
document$.subscribe(({ body }) => {
  renderMathInElement(body, {
    delimiters: [
      { left: "\\(", right: "\\)", display: false },
      { left: "\\[", right: "\\]", display: true },
    ],
  });
});
