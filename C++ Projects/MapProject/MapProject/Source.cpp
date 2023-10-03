#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m;

    assert(m.insert("Junior", 123)); // Asserts you added Junior
    assert(m.insert("Abraham", 456)); //Asserts you added Abraham
    assert(m.erase("Abraham")); //Assert you erased Abraham

    Map m1;
    m1 = m; // Equal Operator

    double d;
    assert(m.size() == m1.size()); // Check the size
    assert(m1.insert("whooo", 12)); // Assert that you inserted “whooo” with value 12.
    assert(m.size() != m1.size()); // Check the size and they should not be equal.
    assert(m1.get("Junior", d) && d == 123); // Checks if there is a node James and if it has the same value 
    assert(!m1.get("Abraham", d) && d != 456); // Checks if there is not a node Abraham and if it does not have a value equal to 456 
    assert(!m.get("whooo", d));


}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}