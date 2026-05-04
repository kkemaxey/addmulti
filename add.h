#ifndef ADD_H
#define ADD_H
using namespace std;

//Allows for any number of fractions to be added or multiplied
const int MAX_SIZE = 2;

//A struct to hold the numerator, denominator, and whole number of a fraction
struct fraction
{
    unsigned long long numerator = 0;
    unsigned long long denominator = 0;
    unsigned long long wholeNumber = 0;
};

//An enum to hold the operation to be performed
enum operation
{
    ADD = 0,
    MULTIPLY = 1
};

//Allows abstraction of the fraction list so that not every function has to be passed the list directly
class FractionList
{
    private:
        fraction fractions[MAX_SIZE];
        int size = MAX_SIZE;

    public:
        void getInput();
        fraction add();
        fraction multiply();
        fraction getFraction(int i) const;
        int getSize() const;
};

bool checkFractionParts(char bar, char slash, unsigned long long denominator);
void display(FractionList, fraction, int);
void simplify(fraction& f);
unsigned long long GCD(unsigned long long, unsigned long long);
unsigned long long LCM(unsigned long long, unsigned long long);

#endif