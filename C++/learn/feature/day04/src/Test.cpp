#include <iostream>

#include "Test.h"

using namespace std;
Test::Test()
{

}

Test::~Test() 
{

}

void Test::Print() {
    cout << "cintvalue = " << ciintvalue << endl;
    cout << "ccharvalue = " << ccharvalue << endl;
}