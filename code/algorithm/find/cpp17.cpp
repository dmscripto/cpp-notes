// std::find in C++17. The page shows the "example" section; the asserts
// below it check that the comments in the example are true.
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

int main() {
    // --8<-- [start:example]
    std::vector<int> v{3, 1, 4, 1, 5};

    // Iterator to the first 4, or v.end() if there is none.
    auto it = std::find(v.begin(), v.end(), 4);
    auto index = it - v.begin();                       // 2
    bool has_9 = std::find(v.begin(), v.end(), 9) != v.end();  // false

    // The first element that satisfies a predicate.
    auto big = std::find_if(v.begin(), v.end(),
                            [](int x) { return x > 3; });       // *big == 4
    auto even = std::find_if_not(v.begin(), v.end(),
                                 [](int x) { return x % 2; });  // *even == 4

    // Search by a member: compare the field in a lambda.
    struct User {
        std::string name;
        int age;
    };
    std::vector<User> users{{"Ann", 31}, {"Bob", 25}};
    auto bob = std::find_if(users.begin(), users.end(),
                            [](const User& u) { return u.name == "Bob"; });
    // bob->age == 25

    // If with an initializer (C++17) keeps the iterator local.
    if (auto pos = std::find(v.begin(), v.end(), 1); pos != v.end()) {
        *pos = 10;                                     // v == {3, 10, 4, 1, 5}
    }
    // --8<-- [end:example]

    assert(index == 2);
    assert(!has_9);
    assert(*big == 4);
    assert(*even == 4);
    assert(bob != users.end() && bob->age == 25);
    assert((v == std::vector{3, 10, 4, 1, 5}));
}
