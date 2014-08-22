#include <iostream>

/*声明内联函数*/
inline int Double(int);
using namespace std;

int Double(int target)
{
    return 2*target;

}

int main()
{
    int target;

    cout << "请输入一个整数："<< endl;
    cin >> target;

    target = Double(target);
    cout << "target:\t" << target << endl;

    target = Double(target);
    cout << "target:\t" << target << endl;

    target = Double(target);
    cout << "target:\t" << target << endl;
    return 0;
}

