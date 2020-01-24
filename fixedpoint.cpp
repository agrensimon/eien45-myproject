#include <iostream>

using namespace std;

// 0101 1111 010.1 0001
const uint16_t scale = 6;
const uint16_t FRACTIONAL_MASK = 0xffff >> (16 - scale); //0000 0000 1111 1111
const uint16_t INTEGER_MASK = -1 ^ FRACTIONAL_MASK;
int32_t temp;

#define double_to_fixed(x) ((x) * (double)(1 << scale))
#define fixed_to_double(x) ((double)(x) / (double)(1 << scale))
#define int_to_fixed(x) ((x) << scale)
#define fixed_to_int(x) ((x) >> scale)
#define fraction_part(x) ((x) & FRACTIONAL_MASK)
#define integer_part(x) ((x) & INTEGER_MASK)
#define times_two_power(x, n) ((x) << n)
#define MUL(x,y) 

int muliply(int16_t x, int16_t y)
{
    temp = (int32_t)x * (int32_t)y;
    //temp = temp + (1 << (scale - 1));
    temp >> scale;
    if (temp > INT16_MAX)
    {
        return INT16_MAX;
    }
    else if (temp < INT16_MIN)
    {
        return INT16_MIN;
    }
    else
    {
        return temp;
    }
}

//addition, subtraction is like normal
//++ or -- is addition/subtraction of epsilon

void ranges()
{
    int16_t epsilon = 1;
    int16_t biggest = INT16_MAX;

    cout << "Smallest possible double to represent: " << fixed_to_double(epsilon) << endl;
    cout << "Which in integer form is: " << epsilon << endl;

    cout << "Biggest possible double to represent: " << fixed_to_double(biggest) << endl;
    cout << "Which in integer form is: " << biggest << endl;
}

int main()
{
    cout.precision(5);
    //ranges();
    int16_t x = double_to_fixed(-150);
    int16_t y = double_to_fixed(0.1);
    int16_t res = muliply(x, y);
    //cout << fixed_to_double(1) << endl;
    //cout << "Result is: " << fixed_to_double(res) << endl;
    //cout << res << endl;
    cout << "0.625 = " << double_to_fixed(0.625) << endl;
    cout << "0.8 = " << double_to_fixed(0.8) << endl;
    cout << "0.524288 = " << double_to_fixed(0.524288) << endl;
    cout << "0.625 = " << double_to_fixed(0.625) << endl;
    cout << "0.8 = " << ((0.8) * (double)(1 << scale)) << endl;
    //cin.get();
    return 0;
}
