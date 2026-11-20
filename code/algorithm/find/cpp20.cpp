// std::ranges::find in C++20. The page shows the "example" section; the
// asserts below it check that the comments in the example are true.
#include <algorithm>
#include <array>
#include <cassert>
#include <ranges>
#include <string>
#include <vector>

int main() {
    // --8<-- [start:example]
    std::vector<int> v{3, 1, 4, 1, 5};

    // Pass the whole range instead of begin() and end().
    auto it = std::ranges::find(v, 4);                 // *it == 4
    bool has_9 = std::ranges::find(v, 9) != v.end();   // false
    auto big = std::ranges::find_if(v, [](int x) { return x > 3; });  // 4

    // Projection: search by a member without writing a lambda.
    struct User {
        std::string name;
        int age;
    };
    std::vector<User> users{{"Ann", 31}, {"Bob", 25}};
    auto bob = std::ranges::find(users, "Bob", &User::name);  // bob->age == 25
    auto young = std::ranges::find_if(users, [](int age) { return age < 30; },
                                      &User::age);            // young == bob

    // Views work too: the first square greater than 10.
    auto squares = v | std::views::transform([](int x) { return x * x; });
    auto sq = std::ranges::find_if(squares, [](int x) { return x > 10; });
    // *sq == 16

    // constexpr: the search can run at compile time.
    constexpr std::array primes{2, 3, 5, 7};
    static_assert(std::ranges::find(primes, 5) == primes.begin() + 2);
    // --8<-- [end:example]

    assert(*it == 4 && it - v.begin() == 2);
    assert(!has_9);
    assert(*big == 4);
    assert(bob != users.end() && bob->age == 25);
    assert(young == bob);
    assert(*sq == 16);
}
