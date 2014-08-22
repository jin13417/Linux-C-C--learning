#include <iostream>

int x = 5;
int y = 7;

void myfunction()
{
    using namespace std;

    int y = 10;
    cout << "********myfunction start******" << endl;
    cout << "myfunction x = " << x << endl;
    cout << "myfunction y = " << y << endl;
    cout << "********myfunction end******" << endl;

    return;
}
int main()
{
    using namespace std;
    cout << "执行函数myfunction 前：" << endl;
    cout << "main x = " << x << endl;
    cout << "main y = " << y << endl;

    myfunction();
    cout << "执行函数myfunction 后：" << endl;
    cout << "main x = " << x << endl;
    cout << "main y = " << y << endl;

    return 0;
}
