#include <iostream>
using namespace std;

double max(double d1, double d2)
{
    return (d1 > d2)?d1:d2;
}

int max(int d1, int d2)
{
    return (d1 > d2)?d1:d2;
}

int main()
{
    cout << "max(12,8) = " << max(12,8)<< endl;
    cout << "max(12.9,8.8) = " << max(12.9,8.8) << endl;
    return 0;
}

