#include <string>
#include <iostream>

int main()
{
    using namespace std;
    /*声明并定义一个string对象*/
    string str1 ("This is a C++ string! ");

    cout << "str1 = " << str1 << endl;

    string str2;
    str2 = str1;

    cout << "str2 = " << str2 << endl;
    
    /*直接赋值*/
    str2 = "Hello string!";
    cout << "赋值后的 str2 = " << str2 << endl;

    string str3;

    str3 = str1 + str2;

    cout << "the result of str1 + str2 is = " << str3 << endl;

    return 0;
}
