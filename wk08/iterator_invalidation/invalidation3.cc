#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */
void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    using Iter = std::vector<int>::iterator;

    //Iter begin = vec.begin();
    //Iter end = vec.end();
    for ( unsigned long it = 0; it < vec.size(); it++){
        if ( vec[it] % 2 == 0 ){
            vec.insert(vec.begin()+it, vec[it]);
            it++;
        }
        else {
            vec.erase(vec.begin()+it);
            it--;
        }
    }
}

