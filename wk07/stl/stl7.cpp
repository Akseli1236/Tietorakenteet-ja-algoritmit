#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    int n = v.size();
    if (n == 0){
        return NOT_FOUND;
    }
    if (n % 2 == 0){
        return 0.5 * (v[n/2] + v[n/2-1]);
    }else{
        nth_element(v.begin(), v.begin() + n / 2, v.end());
        return v[(n-1) / 2];
    }

}

