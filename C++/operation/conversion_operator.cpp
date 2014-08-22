/*
 *conversion_operator.cpp
 *cDate : 2013-9-29
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*C++中的转换运算符
 * 基本格式：
 *operator 数据类型（）
 * */

class cDate {
private:
    int m_nDay; //范围 1-30(按照每月30天计算）
    int m_nMonth; // 1-12
    int m_nYear;
public:
    cDate (int nDay,int nMonth,int nYear)
        :m_nDay(nDay),m_nMonth(nMonth),m_nYear(nYear){};
    operator int(){
        return (m_nYear*10000 + m_nMonth*100 + m_nDay);
    }
    void DisplayDate(){
        cout << m_nDay<<"/"<<m_nMonth<<"/"<<m_nYear<<endl;
    }
};

int main()
{
    cDate mdate(29,10,2013);
    mdate.DisplayDate();

    int nDate = mdate;

    cout << "the interger of the date is:" << nDate <<endl;
}
        
