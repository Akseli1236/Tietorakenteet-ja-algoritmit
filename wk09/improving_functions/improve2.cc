#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

using namespace std;
/**
 * @brief Gets the smallest value from the vector passed as a parameter.
 *
 * @param vec vector which is searched for the smallest value.
 * @return int - the smallest value or 0 (zero) if vector is empty.
 */
int minValue(std::vector<int> vec){
    if ( vec.empty() ) { return 0; }
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int>::iterator result = std::min_element(vec.begin(), vec.end());
    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1e6;
    std::cout << "Time taken by program is: " << time_taken << " sec " << *result << std::endl;
    return *result;



}
