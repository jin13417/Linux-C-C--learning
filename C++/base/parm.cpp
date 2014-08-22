#include <iostream>
int area(int length,int width = 25, int height = 1);

int area(int length,int width,int height)
{
    return length*width*height;
}
int main()
{
    using namespace std;

    int length = 100;
    int width = 50;
    int height = 2;

    cout << "area(length,width,height) is :" << area(length,width,height) << endl;
    cout << "area(length,width) is :" << area(length,width) << endl;
    cout << "area(length) is :" << area(length) << endl;

    return 0;

}
