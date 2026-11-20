#include "sorting/bubble_sort.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <string>
#include <utility>
#include <vector>

namespace {

int failures = 0;

void check(bool ok, const char* what) {
    if (!ok) {
        std::printf("    check failed: %s\n", what);
        ++failures;
    }
}

void test_simple_version() {
    const std::vector<std::vector<int>> cases = {
        {},
        {42},
        {2, 1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {3, 1, 3, 1, 2, 2},
        {-5, 0, -1, 7, -5},
    };
    for (auto a : cases) {
        auto expected = a;
        std::sort(expected.begin(), expected.end());
        bubble_sort(a);
        check(a == expected, "simple version sorts small cases");
    }
}

void test_generic_version_random() {
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> value(-50, 50);
    for (int size = 0; size < 40; ++size) {
        std::vector<int> a(static_cast<std::size_t>(size));
        for (auto& x : a)
            x = value(rng);
        auto expected = a;
        std::sort(expected.begin(), expected.end());
        bubble_sort(a.begin(), a.end());
        check(a == expected, "generic version matches std::sort");
    }
}

void test_custom_comparator() {
    std::vector<int> a = {1, 5, 2, 4, 3};
    bubble_sort(a.begin(), a.end(), std::greater<>{});
    check(a == std::vector<int>{5, 4, 3, 2, 1}, "std::greater sorts descending");
}

void test_stability() {
    // Sort by key only; equal keys must keep their original order.
    std::vector<std::pair<int, std::string>> a = {
        {2, "a"}, {1, "b"}, {2, "c"}, {1, "d"}, {0, "e"},
    };
    bubble_sort(a.begin(), a.end(),
                [](const auto& l, const auto& r) { return l.first < r.first; });
    const std::vector<std::pair<int, std::string>> expected = {
        {0, "e"}, {1, "b"}, {1, "d"}, {2, "a"}, {2, "c"},
    };
    check(a == expected, "equal keys keep their order (stable)");
}

}  // namespace

int main() {
    test_simple_version();
    test_generic_version_random();
    test_custom_comparator();
    test_stability();
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
