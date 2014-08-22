/*
 *subscript_operator.cpp
 *cDate : 2013-11-09
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

class cArray{
private:
    int* m_pIntArray;
    int m_nNumElements;
public:
    cArray(int nNum);
    ~cArray();
    //下标操作符
    int & operator [] (int index);
};

/*下标操作运算符号*/
int & cArray::operator [](int index)
{
    return m_pIntArray[index];
}

/*构造函数*/
cArray::cArray(int nNum)
{
    m_pIntArray = new int[nNum];
    m_nNumElements = nNum;
}

/*析构函数*/
cArray::~cArray()
{
    delete [] m_pIntArray;
    cout << "cArray destruction..." << endl;
}

int main()
{
    cArray mArray(5);
    int i;
    for(i = 0; i < 5; i++){
        mArray[i] = i*5;
    }
    
    /*print*/
    cout << "output mArray[0-4]:"<<endl;
    for(i = 0; i < 5; i++){
        cout << mArray[i] << "\t";
    }
    cout << endl;

}
