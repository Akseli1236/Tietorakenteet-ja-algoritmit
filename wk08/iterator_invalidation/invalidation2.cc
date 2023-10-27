#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
    auto beg = vec.begin();
    auto end = vec.end();
    vec.erase(remove_if(beg, end, [counter = 0](const auto it) mutable {return ++counter % 2 == 0;}),end);
}

