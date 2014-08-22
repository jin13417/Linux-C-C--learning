/*
 *macr0_expansion.cpp
 *cDate : 2013-11-16
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*在宏中使用括号
 *宏与函数及模板之比较
 * 1、宏在每次被使用时都按内联方式展开
 * 2、速度比函数调用快，没有函数调用的开销
 * 3、宏不能出现在编译器使用的中间源代码中，调试器无法看到，宏调试比较棘手
 * 4、宏不是类型安全的，宏几乎可以提供任何类型的参数
 * */

#define CUBE(a) ((a)*(a)*(a))
#define THREE(a) a*a*a

int main()
{
    long x = 5;

    cout <<" CUBE(" << x  <<"): " << CUBE(x) << endl;
    cout <<" THREE(" << x  <<"): " << THREE(x) << endl;

    long a = 5,b= 7;

    /* (5 + 7)*(5 + 7)*(5 + 7) */
    cout <<" CUBE(5 + 7): " << CUBE(a + b) << endl;
    /* 5 + 7 *5 + 7*5 + 7 */
    cout <<" THREE(5  + 7): " << THREE(a + b) << endl;

    return 0;
}
