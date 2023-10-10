#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    try {
        int firstHalf = 0;
        int secondHalf = 0;
        std::vector<int> temp = {};
        for_each(v.begin(),v.end(), [&firstHalf, &temp, &secondHalf](int &element){

            if (element % 3 == 0){
                firstHalf++;
                temp.insert(temp.begin(), element);
                sort(temp.begin(), temp.begin() + firstHalf);
            }else if (element % 3 == 1){
                secondHalf++;
                temp.insert(temp.begin() + firstHalf, element);
                sort(temp.begin()+ firstHalf, temp.begin() + firstHalf + secondHalf);
            }else if (element % 3 == 2){

                temp.push_back(element);
                sort(temp.begin() + firstHalf + secondHalf, temp.end());

            }
        });

        v = temp;
        return EXIT_SUCCESS;

    } catch (...) {
        return EXIT_FAILURE;
    }


}

