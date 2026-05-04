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
        unsigned long long num;
        unsigned long long den;
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

bool checkFractionParts(char bar, char slash, unsigned long long denominator)
{
    return bar == '|' && slash == '/' && denominator != 0;
}


//--------------------------------------------------------------------
// Accumulates a running fraction across all inputs using the formula:
// a/b + c/d = (a * (d/g)) + (c * (b/g)) / b * (d/g)
// where g = GCD(b, d). Simplifies after every step to keep
// intermediate values small and prevent overflow.
// Once accumulated, decomposes the result into a mixed number.
//--------------------------------------------------------------------

fraction FractionList::add()
{
    fraction running;
    unsigned long long num = 0;
    unsigned long long den = 1;

    for (int i = 0; i < size; i++)
    {
        const unsigned long long a = num;
        const unsigned long long b = den;
        const unsigned long long c = fractions[i].wholeNumber * fractions[i].denominator + fractions[i].numerator;
        const unsigned long long d = fractions[i].denominator;

        const unsigned long long g = GCD(b, d);
        const unsigned long long bReduced = b / g;
        const unsigned long long dReduced = d / g;

        num = a * dReduced + c * bReduced;
        den = bReduced * d;

        const unsigned long long g2 = GCD(num, den);
        num /= g2;
        den /= g2;
    }

    running.wholeNumber = num / den;
    running.numerator = num % den;
    running.denominator = den;
    simplify(running);
    return running;
}


//------------------------------------------------------------------
// Accumulates a running product across all inputs using
// cross-cancellation before each multiplication step:
// 1. Convert current fraction to improper form (whole * den + num)
// 2. Cancel GCD(running numerator, incoming denominator)
// 3. Cancel GCD(incoming numerator, running denominator)
// 4. Multiply reduced values into running totals
// 5. Simplify after each step to prevent overflow
// Once accumulated, decomposes the result into a mixed number.
//------------------------------------------------------------------

fraction FractionList::multiply()
{
    fraction product;
    unsigned long long numerator   = 1;
    unsigned long long denominator = 1;

    for (int i = 0; i < size; i++)
    {
        unsigned long long c = fractions[i].wholeNumber * fractions[i].denominator + fractions[i].numerator;
        unsigned long long d = fractions[i].denominator;

        const unsigned long long g1 = GCD(numerator, d);
        numerator /= g1;
        d /= g1;

        const unsigned long long g2 = GCD(c, denominator);
        c /= g2;
        denominator /= g2;

        numerator *= c;
        denominator *= d;

        const unsigned long long g3 = GCD(numerator, denominator);
        numerator /= g3;
        denominator /= g3;
    }

    product.wholeNumber = numerator / denominator;
    product.numerator   = numerator % denominator;
    product.denominator = denominator;

    simplify(product);
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


//--------------------------------------------------------
// Divides numerator and denominator by their GCD in place
//--------------------------------------------------------

void simplify(fraction& f)
{
    if (f.denominator == 0) return;
    unsigned long long g = GCD(f.numerator, f.denominator);
    f.numerator /= g;
    f.denominator /= g;
}


//--------------------------------------------------------------
// Recursively finds the greatest common divisor of two integers
//--------------------------------------------------------------

unsigned long long GCD(unsigned long long a, unsigned long long b)
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

unsigned long long LCM(unsigned long long a, unsigned long long b)
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