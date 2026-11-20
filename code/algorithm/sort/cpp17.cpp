// std::sort in C++17. The page shows the "example" section; the asserts
// below it check that the comments in the example are true.
#include <algorithm>
#include <cassert>
#include <execution>
#include <functional>
#include <string>
#include <tuple>
#include <vector>

int main() {
    // --8<-- [start:example]
    std::vector<int> v{5, 2, 9, 1, 7};

    std::sort(v.begin(), v.end());                     // 1 2 5 7 9
    std::sort(v.begin(), v.end(), std::greater<>{});   // 9 7 5 2 1

    // Sort structs: pass a comparator that says "a goes before b".
    struct User {
        std::string name;
        int age;
    };
    std::vector<User> users{{"Cid", 31}, {"Bob", 25}, {"Ann", 31}};
    std::sort(users.begin(), users.end(),
              [](const User& a, const User& b) { return a.age < b.age; });
    // Bob comes first. Ann and Cid are equal by age, so their order is
    // unspecified: std::sort is not stable.

    // Several keys: compare tuples, by age and then by name.
    std::sort(users.begin(), users.end(), [](const User& a, const User& b) {
        return std::tie(a.age, a.name) < std::tie(b.age, b.name);
    });                                                // Bob, Ann, Cid

    // C++17: the same sort, allowed to use several threads.
    // It pays off only for large inputs.
    std::sort(std::execution::par, v.begin(), v.end());  // 1 2 5 7 9
    // --8<-- [end:example]

    assert((v == std::vector{1, 2, 5, 7, 9}));
    assert(users[0].name == "Bob" && users[1].name == "Ann" && users[2].name == "Cid");
}
