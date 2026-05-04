#include <iostream>
#include <string>
#include "add.h"
using namespace std;

//------------------------------------------------------------------
// Reads MAX_SIZE fractions from the user in the format: whole | n/d
//------------------------------------------------------------------

void getInput(fraction arr[])
{
    cout << "Enter " << MAX_SIZE << " fractions (format: whole | numerator/denominator):" << endl;
    
    for (int i = 0; i < MAX_SIZE; i++)
    {
        char bar;
        string fracString;
        bool valid = false;
        
        while (!valid)
        {
            cout << ">> ";
            cin >> arr[i].wholeNumber >> bar >> fracString;
            
            valid = checkInput(fracString);
            
            if (!valid)
            {
                cout << "Invalid fraction format. Please use n/d (e.g. 3/4)." << endl;
            }
        }
        
        int slashPos = fracString.find('/');
        arr[i].numerator   = stoi(fracString.substr(0, slashPos));
        arr[i].denominator = stoi(fracString.substr(slashPos + 1));
    }
}


//------------------------------------------------------------------
// Validates that the fraction string is in the format "n/d"
//------------------------------------------------------------------

bool checkInput(string input)
{
    while (input.empty())
    {
        cout << "Please enter a valid input." << endl;
        cout << ">> ";
        cin >> input;
    }

    int slashPos = input.find('/');
    if (slashPos == string::npos)
    {
        return false;
    }

    string left  = input.substr(0, slashPos);
    string right = input.substr(slashPos + 1);

    if (left.empty() || right.empty())
    {
        return false;
    }

    for (char c : left)
    {
        if (!isdigit(c)) return false;
    }

    for (char c : right)
    {
        if (!isdigit(c)) return false;
    }

    return true;
}


//------------------------------------------------------------------
// Adds MAX_SIZE mixed number fractions using the mixed number method:
// 1. Sum whole number parts separately
// 2. Find LCD across all denominators
// 3. Convert and sum all numerators
// 4. Carry any overflow back into the whole number
// 5. Simplify via GCD
//------------------------------------------------------------------

fraction add(fraction arr[])
{
    fraction sum;

    // Step 1: sum whole number parts
    for (int i = 0; i < MAX_SIZE; i++)
    {
        sum.wholeNumber += arr[i].wholeNumber;
    }

    // Step 2: find LCD across all denominators
    int lcd = arr[0].denominator;
    for (int i = 1; i < MAX_SIZE; i++)
    {
        lcd = LCM(lcd, arr[i].denominator);
    }
    sum.denominator = lcd;

    // Step 3: convert each fraction to LCD and sum numerators
    for (int i = 0; i < MAX_SIZE; i++)
    {
        sum.numerator += arr[i].numerator * (lcd / arr[i].denominator);
    }

    // Step 4: carry overflow into whole number
    if (sum.numerator >= sum.denominator)
    {
        sum.wholeNumber += sum.numerator / sum.denominator;
        sum.numerator    = sum.numerator % sum.denominator;
    }

    // Step 5: simplify
    int g = GCD(sum.numerator, sum.denominator);
    sum.numerator   /= g;
    sum.denominator /= g;

    return sum;
}


//------------------------------------------------------------------
// Multiplies MAX_SIZE mixed number fractions:
// 1. Convert each mixed number to improper form temporarily
// 2. Multiply all numerators and denominators
// 3. Extract whole number from result
// 4. Simplify via GCD
//------------------------------------------------------------------

fraction multiply(fraction arr[])
{
    fraction product;

    int numerator   = 1;
    int denominator = 1;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        int improperNumerator = arr[i].wholeNumber * arr[i].denominator + arr[i].numerator;
        numerator   *= improperNumerator;
        denominator *= arr[i].denominator;
    }

    product.wholeNumber = numerator / denominator;
    product.numerator   = numerator % denominator;
    product.denominator = denominator;

    int g = GCD(product.numerator, product.denominator);
    product.numerator   /= g;
    product.denominator /= g;

    return product;
}


//----------------------------------------------------------------------------------------------------
// This will take in the fractions, the answer, and the operation and display it in the correct format
//----------------------------------------------------------------------------------------------------

void display(fraction arr[], fraction ans, int op)
{
    if (op == ADD)
    {
        cout << "Sum:     ";
    }
    else
    {
        cout << "Product: ";
    }

    for (int i = 0; i < MAX_SIZE; i++)
    {
        // display whole number only if non-zero
        if (arr[i].wholeNumber != 0)
        {
            cout << arr[i].wholeNumber;
        }

        cout << "(" << arr[i].numerator << "/" << arr[i].denominator << ")";

        if (i != MAX_SIZE - 1)
        {
            if (op == ADD)
            {
                cout << " + ";
            }
            else
            {
                cout << " x ";
            }
        }
        else
        {
            cout << " = ";
        }
    }

    if (ans.wholeNumber != 0)
    {
        cout << ans.wholeNumber;
    }

    cout << "(" << ans.numerator << "/" << ans.denominator << ")" << endl;
}


//------------------------------------------------------------------
// Recursively finds the greatest common divisor of two integers
//------------------------------------------------------------------

int GCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return GCD(b, a % b);
    }
}


//------------------------------------------------------------------
// Finds the least common multiple of two integers using GCD
//------------------------------------------------------------------

int LCM(int a, int b)
{
    return (a / GCD(a, b)) * b;
}