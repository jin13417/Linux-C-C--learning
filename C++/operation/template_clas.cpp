

/*
 *template_class.cpp
 *cDate : 2013-9-28
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

template <typename T1=int,typename T2=double>
class CholdPair
{
private:
    T1 m_Value1;
    T2 m_Value2;
public:
    CholdPair(const T1 & value1,const T2 & value2)
    {
        m_Value1 = value1;
        m_Value2 = value2;
    }

    const T1 & getFristValue()
    {
        return m_Value1;
    }

    const T2 & getSecondValue()
    {
        return m_Value2;
    }
};

int main()
{
    //模板实例化
    CholdPair <> mIntFloatPair(111,10.09);
    CholdPair <short,char *> mShortStringPair(25,"I am a good boy!");

    cout << "Value1: " <<mIntFloatPair.getFristValue() <<endl;
    cout << "Value2: " <<mIntFloatPair.getSecondValue() <<endl;

    cout << "Value1: " <<mShortStringPair.getFristValue() <<endl;
    cout << "Value2: " <<mShortStringPair.getSecondValue() <<endl;
    
    return 0;
}


