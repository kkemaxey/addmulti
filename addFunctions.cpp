#include <iostream>
#include <limits>
#include <string>
#include "add.h"
using namespace std;

//------------------------------------------------------------------
// Reads MAX_SIZE fractions from the user in the format: whole | n/d
//------------------------------------------------------------------

void FractionList::getInput()
{
    cout << "Enter " << size << " proper fractions:" << endl;

    for (int i = 0; i < size; i++)
    {
        char bar;
        char slash;
        int num;
        int den;
        bool valid = false;

        while (!valid)
        {
            cout << ">> ";
            if (cin >> fractions[i].wholeNumber >> bar >> num >> slash >> den)
            {
                valid = checkFractionParts(bar, slash, den);
                if (valid)
                {
                    fractions[i].numerator   = num;
                    fractions[i].denominator = den;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    cout << "Invalid fraction format. Use: whole | numerator/denominator (e.g. 2 | 3/4 or 2 | 3 / 4)." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            else
            {
                cout << "Invalid input. Use: whole | numerator/denominator (e.g. 2 | 3/4)." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}


//---------------------------------------------------------------
// Validates bar, slash, and denominator after tokenized >> reads
//---------------------------------------------------------------

bool checkFractionParts(char bar, char slash, int denominator)
{
    return bar == '|' && slash == '/' && denominator != 0;
}


//------------------------------------------------------------------
// Adds MAX_SIZE mixed number fractions using the mixed number method:
// 1. Sum whole number parts separately
// 2. Find LCD across all denominators
// 3. Convert and sum all numerators
// 4. Carry any overflow back into the whole number
// 5. Simplify via GCD
//------------------------------------------------------------------

fraction FractionList::add()
{
    fraction sum;
    for (int i = 0; i < size; i++)
    {
        sum.wholeNumber += fractions[i].wholeNumber;
    }

    int lcd = fractions[0].denominator;
    for (int i = 1; i < size; i++)
    {
        lcd = LCM(lcd, fractions[i].denominator);
    }
    sum.denominator = lcd;

    for (int i = 0; i < size; i++)
    {
        sum.numerator += fractions[i].numerator * (lcd / fractions[i].denominator);
    }

    if (sum.numerator >= sum.denominator)
    {
        sum.wholeNumber += sum.numerator / sum.denominator;
        sum.numerator    = sum.numerator % sum.denominator;
    }
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

fraction FractionList::multiply()
{
    fraction product;
    int numerator   = 1;
    int denominator = 1;

    for (int i = 0; i < size; i++)
    {
        int improperNumerator = fractions[i].wholeNumber * fractions[i].denominator + fractions[i].numerator;
        numerator   *= improperNumerator;
        denominator *= fractions[i].denominator;
    }

    product.wholeNumber = numerator / denominator;
    product.numerator   = numerator % denominator;
    product.denominator = denominator;

    int g = GCD(product.numerator, product.denominator);
    product.numerator   /= g;
    product.denominator /= g;

    return product;
}


//----------------------------------------
// Returns the fraction at the given index
//----------------------------------------

fraction FractionList::getFraction(int i) const 
{ 
    return fractions[i]; 
}


//--------------------------------------
// Returns the size of the fraction list
//--------------------------------------

int FractionList::getSize() const 
{ 
    return size; 
}


//----------------------------------------------------------------------------------------------------
// This will take in the fractions, the answer, and the operation and display it in the correct format
//----------------------------------------------------------------------------------------------------

void display(FractionList list, fraction ans, int op)
{
    cout << (op == ADD ? "Sum:     " : "Product: ");

    for (int i = 0; i < list.getSize(); i++)
    {
        fraction f = list.getFraction(i);

        (f.wholeNumber != 0 ? cout << f.wholeNumber : cout)
            << "(" << f.numerator << "/" << f.denominator << ")"
            << (i != list.getSize() - 1 ? (op == ADD ? " + " : " x ") : " = ");
    }

    (ans.wholeNumber != 0 ? cout << ans.wholeNumber : cout)
        << "(" << ans.numerator << "/" << ans.denominator << ")" << endl;
}


//--------------------------------------------------------------
// Recursively finds the greatest common divisor of two integers
//--------------------------------------------------------------

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


//----------------------------------------------------------
// Finds the least common multiple of two integers using GCD
//----------------------------------------------------------

int LCM(int a, int b)
{
    return (a / GCD(a, b)) * b;
}


//In case the display function was too hard to read, here's the same function but without ternaries
// void display(FractionList list, fraction ans, int op)
// {
//     if (op == ADD)
//     {
//         cout << "Sum:     ";
//     }
//     else
//     {
//         cout << "Product: ";
//     }

//     for (int i = 0; i < list.getSize(); i++)
//     {
//         fraction f = list.getFraction(i);

//         if (f.wholeNumber != 0)
//         {
//             cout << f.wholeNumber;
//         }

//         cout << "(" << f.numerator << "/" << f.denominator << ")";

//         if (i != list.getSize() - 1)
//         {
//             if (op == ADD)
//             {
//                 cout << " + ";
//             }
//             else
//             {
//                 cout << " x ";
//             }
//         }
//         else
//         {
//             cout << " = ";
//         }
//     }

//     if (ans.wholeNumber != 0)
//     {
//         cout << ans.wholeNumber;
//     }

//     cout << "(" << ans.numerator << "/" << ans.denominator << ")" << endl;