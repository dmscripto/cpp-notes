// std::ranges::sort in C++20. The page shows the "example" section; the
// asserts below it check that the comments in the example are true.
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <string>
#include <tuple>
#include <vector>

int main() {
    // --8<-- [start:example]
    std::vector<int> v{5, 2, 9, 1, 7};

    std::ranges::sort(v);                              // 1 2 5 7 9
    std::ranges::sort(v, std::ranges::greater{});      // 9 7 5 2 1

    // Projection: sort by a member, no comparator lambda needed.
    struct User {
        std::string name;
        int age;
    };
    std::vector<User> users{{"Cid", 31}, {"Bob", 25}, {"Ann", 31}};
    std::ranges::sort(users, {}, &User::name);         // Ann, Bob, Cid
    std::ranges::sort(users, std::ranges::greater{}, &User::age);
    // Ann or Cid first (31), Bob last (25)

    // Several keys: project to a tuple, by age and then by name.
    std::ranges::sort(users, {}, [](const User& u) { return std::tie(u.age, u.name); });
    // Bob, Ann, Cid

    // constexpr: sorting can run at compile time.
    constexpr auto sorted = [] {
        std::array a{3, 1, 2};
        std::ranges::sort(a);
        return a;
    }();
    static_assert(sorted == std::array{1, 2, 3});
    // --8<-- [end:example]

    assert((v == std::vector{9, 7, 5, 2, 1}));
    assert(users[0].name == "Bob" && users[1].name == "Ann" && users[2].name == "Cid");
}
