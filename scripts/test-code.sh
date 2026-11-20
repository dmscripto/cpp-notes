#!/usr/bin/env bash
# Compiles and runs the C++ code shown on the site:
#   *_test.cpp   tests, compiled as C++20
#   cppNN.cpp    examples, compiled with -std=c++NN (cpp17.cpp -> C++17, ...)
#
# Usage: bash scripts/test-code.sh                       (everything in code/)
#        bash scripts/test-code.sh code/algorithm/find   (only these paths)
#        CXX=clang++ bash scripts/test-code.sh
set -euo pipefail

cd "$(dirname "$0")/.."

CXX="${CXX:-g++}"
FLAGS=(-Wall -Wextra -Wpedantic -Werror -O1 -g -I code)

# Sanitizers are not available with MinGW on Windows.
case "$(uname -s)" in
  Linux* | Darwin*) FLAGS+=(-fsanitize=address,undefined -fno-omit-frame-pointer) ;;
esac

[ "$#" -gt 0 ] || set -- code

mkdir -p build
failed=0
count=0

while IFS= read -r -d '' file; do
  count=$((count + 1))
  base="$(basename "$file")"
  case "$base" in
    cpp[0-9][0-9].cpp) std="c++${base:3:2}" ;;
    *) std="c++20" ;;
  esac
  # code/algorithm/find/cpp17.cpp -> build/algorithm_find_cpp17
  name="${file#code/}"
  name="${name%.cpp}"
  name="${name//\//_}"
  echo "==> $file ($std)"
  if "$CXX" -std="$std" "${FLAGS[@]}" -o "build/$name" "$file" && "./build/$name"; then
    echo "    ok"
  else
    echo "    FAILED"
    failed=$((failed + 1))
  fi
done < <(find "$@" \( -name '*_test.cpp' -o -name 'cpp[0-9][0-9].cpp' \) -print0 | sort -z)

echo
echo "$count file(s), $failed failed"
[ "$count" -gt 0 ] && [ "$failed" -eq 0 ]
