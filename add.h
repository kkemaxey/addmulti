#ifndef ADD_H
#define ADD_H
using namespace std;

//Allows for any number of fractions to be added or multiplied
const int MAX_SIZE = 2;

//A struct to hold the numerator, denominator, and whole number of a fraction
struct fraction
{
    int numerator = 0;
    int denominator = 0;
    int wholeNumber = 0;
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

bool checkInput(string);
void display(FractionList, fraction, int);
int GCD(int, int);
int LCM(int, int);

#endif