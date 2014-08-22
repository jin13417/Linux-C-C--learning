/*
 *swap.cpp
 *Date : 2013-9-20
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
#define N 0
using namespace std;
void swap2(int *x,int *y)
{
    int temp;
    cout << "*******************swap2(传递地址)************************" << endl;
    cout << "before swap x :" << x <<"\t y :"<<y <<endl;
    cout << "before swap &x :" << &x <<"\t &y :"<< &y <<endl;
    temp = *x;
    *x = *y;
    *y = temp;
    cout << "after swap x :" << x <<"\t y :"<<y <<endl;
    cout << "after swap &x :" << &x <<"\t &y :"<< &y <<endl;
    cout << "*******************swap2(传递地址)************************" << endl;

}
#if N
void swap(int &x, int &y)
#else
void swap(int x, int y)
#endif
{
    int temp;
    cout << "*******************swap()************************" << endl;
    if(N == 1){
        cout << "引用实现数据交换" << endl;
    }else{
        cout << "普通实现数据交换（错误的数据交换）"<<endl;
    }
    cout << "before swap &x :" << &x <<"\t &y :"<<&y <<endl;
    temp = x;
    x = y;
    y = temp;
    cout << "after swap &x :" << &x <<"\t &y :"<<&y <<endl;
    cout << "*******************swap()************************" << endl;
    
}
int main()
{
    int x = 5, y = 10;
    cout << "验证引用下数据交换" << endl;
    cout << "before swap, x: "<< x << "\t y: " << y << endl;
    cout << "before swap, &x: "<< &x << "\t &y: " << &y << endl;
   // swap(x,y);
    swap2(&x,&y);/*使用指针传递*/
    cout << "after swap, x: "<< x << "\t y: " << y << endl;
    cout << "after swap, &x: "<< &x << "\t &y: " << &y << endl;
    return 0;
}
