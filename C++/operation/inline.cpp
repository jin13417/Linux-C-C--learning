
/*
 *inline.cpp
 *cDate : 2013-11-16
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/* 被声明为内联，像宏一样每次调用时将就地展开
 *没有函数调用的开销。
 * */
inline unsigned long square(unsigned long a)
{
    return a*a;
}

inline unsigned long cube(unsigned long a)
{
    return a*a*a;
}

int main()
{
    unsigned long x;
    for(;;){
        cout << "请输入一个无符号整型(输入0时，退出）：" << endl;
        cin >> x;

        if(x == 0){
            break;
        }

        cout << " you entered : " << x<<endl;
        cout << "\t square(" << x << "):\t" << square(x) <<endl;
        cout << "\t cube(" << x << "):\t" << cube(x) <<endl;

    }
    return 0;
}    
