/*
 *binary_operator+=.cpp
 *cDate : 2013-10-30
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*C++中匀速符+=与-=的编程
 * 加并赋值运算符支持语法a+=b;这让程序员可将对象a+=b
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
    void operator +=(int nDaysToadd);
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


/*a += b*/
void cDate::operator +=(int nDaysToadd)
{
    AddDays(nDaysToadd);
    //mdate.DisplayDate();
    return ;
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
    
    mdate += 10;
    mdate.DisplayDate();
    return 0;
}
        
