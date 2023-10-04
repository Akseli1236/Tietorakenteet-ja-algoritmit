/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration2.hh"
using namespace std;


void printEverySecond(const list<int>& lst)
{
    for (auto it=lst.begin(); it != lst.end(); advance(it, 2)){
        cout << *it << " ";
    }
    cout << endl;
    // ADD YOUR CODE HERE
}
