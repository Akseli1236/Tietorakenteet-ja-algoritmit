/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    auto middle = lst.begin();
    advance(middle, distance(lst.begin(),lst.end())/2);
    for (auto it=lst.begin(); it != middle; it++){
        cout << *it << " ";
    }
    cout << endl;
    // ADD YOUR CODE HERE
}
