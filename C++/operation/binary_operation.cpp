

/*
 *operator.cpp
 *cDate : 2013-9-28
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*C++中的双目运算符
 * 全局函数或者静态成员函数实现基本格式：
 * 返回值类型  operator 操作符号（参数1，参数2）。
 * 以类成员的方式实现的双目运算符的定义如下：
 * 返回值类型 operator 操作符号（参数1）。
 * C++运算符分为2类 ：单目与双目运算符
 * */

class cDate {
private:
    int m_nDay; //范围 1-30(按照每月30天计算）
    int m_nMonth; // 1-12
    int m_nYear;
    void AddDays(int nDaysToadd);
    void AddMonths(int nMonthsToadd);
    void AddYears(int nYearToadd);
public:
    cDate(int nDay,int nMonth,int nYear)
        :m_nDay(nDay),m_nMonth(nMonth),m_nYear(nYear){cout << "cDate coreate..." << endl;};
    ~cDate() {cout << "cDate destory..." << endl;}

    /*操作符重载 operator */
    cDate operator +(int nDaysToadd);
    void DisplayDate();
};

/*add days*/
void cDate::AddDays(int nDaysToadd)
{
    m_nDay += nDaysToadd;
    if(m_nDay > 30){
        AddMonths(m_nDay/30);
        m_nDay %= 30;
    }
}

/*Add Months*/
void cDate::AddMonths(int nMonthsToadd)
{
    m_nMonth += nMonthsToadd;
    if(m_nMonth > 12){
        AddYears(m_nMonth/12);
        m_nMonth %= 12;
    }
}

/*Add Years*/
void cDate::AddYears(int nYearToadd)
{
    m_nYear += nYearToadd;
}


/*x++*/
cDate cDate::operator +(int nDaysToadd)
{
    cDate mdate(m_nDay,m_nMonth,m_nYear);
    mdate.AddDays(nDaysToadd);
    //mdate.DisplayDate();
    return mdate;
}

/*output*/
void cDate::DisplayDate()
{
    cout << m_nDay <<"/"<< m_nMonth << "/" << m_nYear<< endl;
}

int main()
{
    cDate mdate(25,6,2013);
    mdate.DisplayDate();
    

    cout << "**********Adding 10 (days)***********"<<endl;
    
    cDate datePlus10(mdate + 10);
    datePlus10.DisplayDate();
    return 0;
}
        
