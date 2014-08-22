#include <iostream>
/*C++ 内存分配、使用和删除指针*/

using namespace std;

int main()
{

    int localVariable = 5;
    int *pLocal = &localVariable;
    /*申请空间*/
    int *pHeap = new int;

    *pHeap = 7;

    cout << "localVariable:" << localVariable << endl;
    cout << "*pLocal:" << *pLocal << endl;
    cout << "*pHeap:" << *pHeap << endl;
    /*释放空间*/
    delete pHeap;

    pHeap = new int;

    *pHeap = 9;
    cout << "pHeap: " << *pHeap << endl;
    delete pHeap;

    return 0;
}
