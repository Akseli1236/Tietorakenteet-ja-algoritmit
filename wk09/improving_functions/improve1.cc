#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <numeric>


/**
 * @brief creates a vector of integers with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 * @return std::vector<int>
 */
std::vector<int> ascendingVector(int n){
    //time_t start, end;
    std::vector<int> v(n);
    std::iota (v.begin(), v.end(), 0);


    //time(&start);
    /*
    for ( int i = 0; i < n ; i++){
        v.insert(v.end(), i);
    }

    time(&end);
    double time_taken = double(end - start);
    std::cout << "Time taken by program is : " << std::fixed
         << time_taken << std::setprecision(5);
    std::cout << " sec " << std::endl;
*/
    return v;
}
