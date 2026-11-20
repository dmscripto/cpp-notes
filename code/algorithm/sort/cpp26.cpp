// Sorting in C++23 and C++26. The page shows the "example" section; the
// asserts below it check that the comments in the example are true.
#include <algorithm>
#include <array>
#include <cassert>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

int main() {
    // --8<-- [start:example]
    // C++23: sort two parallel vectors together, by the first one.
    std::vector<int> ids{3, 1, 2};
    std::vector<std::string> names{"Cid", "Ann", "Bob"};
    std::ranges::sort(std::views::zip(ids, names));
    // ids == {1, 2, 3}, names == {"Ann", "Bob", "Cid"}

    // C++26: stable_sort is constexpr too (sort has been since C++20).
    constexpr auto ranked = [] {
        std::array<std::pair<int, char>, 4> a{{{2, 'a'}, {1, 'b'}, {2, 'c'}, {1, 'd'}}};
        std::ranges::stable_sort(a, {}, &std::pair<int, char>::first);
        return a;
    }();
    // equal keys keep their order: b, d, a, c
    static_assert(ranked[0].second == 'b' && ranked[1].second == 'd');
    // --8<-- [end:example]

    assert((ids == std::vector{1, 2, 3}));
    assert((names == std::vector<std::string>{"Ann", "Bob", "Cid"}));
    assert(ranked[2].second == 'a' && ranked[3].second == 'c');
}
