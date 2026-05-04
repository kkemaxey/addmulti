#include <iostream>
#include <string>
#include <vector>
#include "addFunctions.cpp"
using namespace std;

//------------------------------------------------------------------
// This will handle call the other functions and display the results
//------------------------------------------------------------------

int main()
{
    fraction inputs[MAX_SIZE];
    getInput(inputs);
    fraction sum = add(inputs);
    fraction product = multiply(inputs);
    display(inputs, sum, ADD);
    display(inputs, product, MULTIPLY);
    return 0;
}