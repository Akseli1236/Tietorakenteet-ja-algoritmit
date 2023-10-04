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
    unsigned long a = 0;
    for (auto it=lst.begin(); it != lst.end(); advance(it, 2)){
        if (a > lst.size()){
            break;
        }
        cout << *it << " ";
        a +=2 ;
    }
    cout << endl;
    // ADD YOUR CODE HERE
}
