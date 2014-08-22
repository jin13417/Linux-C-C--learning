/*
 *reference.cpp
 *Date : 2013-9-19
 *Author: sjin
 *Mail:413977243@qq.com
 */

#include <iostream>
using namespace std;

int main()
{
    int intone;
#if 1
    int &rSomeRef = intone;//引用必须初始化
#else
    int &rSomeRef;
    rSomeRef = intone;
    /*如果执行这里会报下面的错误，可以自己尝试下
     * reference.cpp:17: error: ‘rSomeRef’ declared as reference but not
     * initialized
     */
#endif
    intone = 5;
    cout << "intone :\t" << intone <<"\t\t rSomeRef :\t" << rSomeRef << endl;
    cout << "&intone :\t" << &intone <<"\t rSomeRef :\t" << &rSomeRef << endl;
    
    rSomeRef = 10;
    cout << "intone :\t" << intone <<"\t\t rSomeRef :\t" << rSomeRef << endl;
    cout << "&intone :\t" << &intone <<"\t rSomeRef :\t" << &rSomeRef << endl;

    /*这个在很多书籍上都强调不要对引用重新赋值。
     * 给引用重新赋值相当于给目标重新赋值。
     * 引用的地址还是和目标变量的地址一致
     */
    cout << "*******************引用重新赋值后*******************" << endl;
    int inttwo = 50;
    rSomeRef = inttwo;
    cout << "intone :\t" << intone <<"\t\t rSomeRef :\t" << rSomeRef << endl;
    cout << "&intone :\t" << &intone <<"\t rSomeRef :\t" << &rSomeRef << endl;
    cout << "inttwo :\t" << inttwo <<"\t\t rSomeRef :\t" << rSomeRef << endl;
    cout << "&inttwo :\t" << &inttwo <<"\t rSomeRef :\t" << &rSomeRef << endl;
    cout << "*****************************************************" << endl;
    return 0;
}
