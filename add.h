#ifndef ADD_H
#define ADD_H
using namespace std;

const int MAX_SIZE = 2;

struct fraction
{
    int numerator = 0;
    int denominator = 0;
    int wholeNumber = 0;
};

enum operation
{
    ADD = 0,
    MULTIPLY = 1
};

void getInput(fraction[]);
bool checkInput(string);
fraction add(fraction[]);
fraction multiply(fraction[]);
void display(fraction[], fraction, int);
int GCD(int, int);
int LCM(int, int);

#endif