/*
 *operator_fun.cpp
 *cDate : 2013-11-09
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//STL容器简单介绍
//顺序容器vector
int main()
{
    /*一个动态的整型数组*/
    vector <int> vecIntArray;

    vecIntArray.push_back(1988);
    vecIntArray.push_back(2);
    vecIntArray.push_back(20);
    vecIntArray.push_back(2013);
    vecIntArray.push_back(11);
    vecIntArray.push_back(2);

    cout << "动态数组的内容是：" << endl;

    vector <int>::iterator iArrayWalker = vecIntArray.begin();

    while ( iArrayWalker != vecIntArray.end() ){
        cout << *iArrayWalker << endl;
        ++ iArrayWalker;
    }

    //查找2013是否存在数组中，并打印在数组中的位置
    vector <int>::iterator iElement = find(vecIntArray.begin(),vecIntArray.end(),2013);

    if(iElement != vecIntArray.end()){
        int nPosition = distance(vecIntArray.begin(),iElement);
        cout << "Value " << *iElement;
        cout << "发现他在数组中的位置是："<< nPosition << endl;
    }
    return 0;
}

