
/*
 *operator_fun.cpp
 *cDate : 2013-11-09
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
#include <string>
using namespace std;

/*operator()函数
 *让对象像函数，他们应用的STL（标准模板库）
 *通常用于stl算法中，用途包含决策
 */

class cDisplay{
public:
    void operator()(string strIn) const
    {
        cout << strIn << endl;
    }
};

int main()
{
    cDisplay m_display;
    m_display("hello,my name is jsh");
    return 0;
}


