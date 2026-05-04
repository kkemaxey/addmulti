#include <iostream>
#include <string>
#include "add.h"
using namespace std;

//------------------------------------------------------------------
// This will handle call the other functions and display the results
//------------------------------------------------------------------

int main()
{
    FractionList list;
    list.getInput();
    fraction sum = list.add();
    fraction product = list.multiply();
    display(list, sum, ADD);
    display(list, product, MULTIPLY);
    return 0;
}   