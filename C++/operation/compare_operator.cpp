

/*
 *compare_operator.cpp
 *cDate : 2013-9-28
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*C++中的运算符
 * 基本格式：
 * 返回值类型  operator 操作符号（参数。。。）
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
    // integer conversion operator
    operator int()const;
    
    //判断是否相等，类似于 if（mdate1 == mdate2)
    bool operator ==(const cDate & mdateObj);

    bool operator ==(int nDateNumber);

    //判断是否不相等，类似于 if（mdate1 == mdate2)
    bool operator !=(const cDate & mdateObj);

    bool operator !=(int nDateNumber);

    //实现运算符 < > <= >=
    bool operator < (const cDate &mdateObj)const;
    bool operator <= (const cDate &mdateObj)const;

    bool operator > (const cDate &mdateObj)const;
    bool operator >= (const cDate &mdateObj)const;

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
cDate::operator int()const
{
    return (m_nDay + m_nMonth*100 + m_nYear*10000);
}

/*output*/
void cDate::DisplayDate()
{
    cout << m_nDay <<"/"<< m_nMonth << "/" << m_nYear<< endl;
}

/*if (mdate1 == mdate2)*/
bool cDate::operator ==(const cDate& mdateObj)
{
    return ((mdateObj.m_nYear == m_nYear)
            &&(mdateObj.m_nMonth == m_nMonth)
            &&(mdateObj.m_nDay == m_nDay));
}

/*if(mdate1 == nDateNumber)*/
bool cDate::operator ==(int nDateNumber)
{
    return nDateNumber == (int)*this;
}

/*if(mdate1 == mdateObj)*/
bool cDate::operator !=(const cDate& mdateObj)
{
    return !(this->operator==(mdateObj));
}

/*if(mdate1 != nDateNumber)*/
bool cDate::operator !=(int nDateNumber)
{
    return !(this->operator == (nDateNumber));
}

/*if (mdate1 > mdateObj)*/
bool cDate::operator > (const cDate &mdateObj)const
{
    return (this->operator int() > mdateObj.operator int());
}

/*if (mdate1 >= mdateObj)*/
bool cDate::operator >= (const cDate &mdateObj)const
{
    return (this->operator int() >= mdateObj.operator int());
}

/*if (mdate1 < mdateObj)*/
bool cDate::operator < (const cDate &mdateObj)const
{
    return (this->operator int() < mdateObj.operator int());
}

/*if (mdate1 <= mdateObj)*/
bool cDate::operator <= (const cDate &mdateObj)const
{
    return (this->operator int() <=  mdateObj.operator int());
}
int main()
{
    cDate mdate1(25,6,2013);
    cout << "mdate1 Display:";
    mdate1.DisplayDate();

    cDate mdate2(5,11,2013);
    cout << " mdate2 Display:";
    mdate2.DisplayDate();
    
    cDate mdate3(5,11,2013);
    cout << " mdate3 Display:";
    mdate3.DisplayDate();

    if(mdate1 != mdate2){
        cout << " mdate1 != mdate2 is correct!" << endl;
    }

    if(mdate2 == mdate3){
        cout << " mdate2 == mdate3 is correct!" << endl;
    }

    int int_mdate3 = mdate3;

    if(mdate2 == int_mdate3){
        cout << " mdate2 == int_mdate1 is correct!" << endl;
    }

    if(mdate1 != int_mdate3){
        cout << " mdate1 != int_mdate3 is correct!" << endl;
    }

    if(mdate1 < mdate2){
        cout << " mdate1 < mdate2 is correct!" << endl;
    }
    if(mdate2 >= mdate3){
        cout << " mdate2 >= mdate3 is correct!" << endl;
    }
    return 0;
}
        
