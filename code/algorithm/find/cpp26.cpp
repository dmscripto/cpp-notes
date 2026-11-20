// Searching in C++23 and C++26. The page shows the "example" section; the
// asserts below it check that the comments in the example are true.
#include <algorithm>
#include <cassert>
#include <vector>

int main() {
    // --8<-- [start:example]
    std::vector<int> v{3, 1, 4, 1, 5};

    // C++23: ask whether the value is there, no iterator needed.
    bool has_4 = std::ranges::contains(v, 4);          // true

    // C++23: search from the back. Returns the subrange [found, end).
    auto tail = std::ranges::find_last(v, 1);
    auto last_index = tail.begin() - v.begin();        // 3

    // C++26: the value can be a braced list, the type comes from the range.
    struct Point {
        int x, y;
        bool operator==(const Point&) const = default;
    };
    std::vector<Point> points{{0, 0}, {2, 3}};
    auto p = std::ranges::find(points, {2, 3});        // p == points.begin() + 1
    auto q = std::find(points.begin(), points.end(), {0, 0});  // classic form too
    // --8<-- [end:example]

    assert(has_4);
    assert(last_index == 3 && tail.size() == 2);
    assert(p == points.begin() + 1);
    assert(q == points.begin());
}
