#include <iterator>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <numeric>

using namespace std;


/**
 * @brief Sums up the values of the vector cumulatively, storing cumulative sum
 *        of the vector in a map, where the keys are the unique vector items,
 *        and the value is the last cumulative sum when that value was last
 *        encountered. (example: {4, 5, 4, 6} => {{4, 13}, {5, 9}, {6, 19}}).
 *
 * @param vec vector which is used for the sum operation.
 * @return std::map<int, int> sums - the sums of each cumulation stored in
 *         a map as values, vector values used as keys.
 */
std::map<int, int> cumulativeSums(std::vector<int> v) {
    auto start = std::chrono::high_resolution_clock::now();
    std::map<int,int> sums;

    //std::vector<int> cumulativeSum(v.size());
    //std::partial_sum(v.begin(), v.end(), cumulativeSum.begin());

    std::accumulate(v.begin(), v.end(), 0, [&](int &acc, int x) {
        acc += x;
        sums[x] = acc;
        return acc;
    });
    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1e6;
    std::cout << "Time taken by program is: " << time_taken  << " sec " <<std::endl;
    return sums;
}
