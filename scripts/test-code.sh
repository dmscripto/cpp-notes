#!/usr/bin/env bash
# Compiles and runs every code/**/*_test.cpp file.
# Usage: bash scripts/test-code.sh          (uses g++)
#        CXX=clang++ bash scripts/test-code.sh
set -euo pipefail

cd "$(dirname "$0")/.."

CXX="${CXX:-g++}"
FLAGS=(-std=c++20 -Wall -Wextra -Wpedantic -Werror -O1 -g)

# Sanitizers are not available with MinGW on Windows.
case "$(uname -s)" in
  Linux* | Darwin*) FLAGS+=(-fsanitize=address,undefined -fno-omit-frame-pointer) ;;
esac

mkdir -p build
failed=0
count=0

while IFS= read -r -d '' test; do
  count=$((count + 1))
  name="$(basename "${test%.cpp}")"
  echo "==> $test"
  if "$CXX" "${FLAGS[@]}" -I code -o "build/$name" "$test" && "./build/$name"; then
    echo "    ok"
  else
    echo "    FAILED"
    failed=$((failed + 1))
  fi
done < <(find code -name '*_test.cpp' -print0 | sort -z)

echo
echo "$count test file(s), $failed failed"
[ "$failed" -eq 0 ]
