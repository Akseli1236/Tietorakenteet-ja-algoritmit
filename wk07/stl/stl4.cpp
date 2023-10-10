#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;

/**
 * @brief Return an iterator which points to the last even integer of the vector
 *        If the value is not found, return v.rend()
 *
 * @param v the vector to be scanned through
 * @return std::vector<int>::reverse_iterator
 */
std::vector<int>::reverse_iterator findLastEven(std::vector<int>& v)
{
    int temp = -1;
    for_each(v.begin(),v.end(), [&temp](int element){
        if (element % 2 == 0){
            temp = element;

        }
    });
    std::vector<int>::reverse_iterator found = v.rend();
    if (temp != -1){
         found = find(v.rbegin(), v.rend(),temp);
    }else{
        return found;
    }

    return found;

}

