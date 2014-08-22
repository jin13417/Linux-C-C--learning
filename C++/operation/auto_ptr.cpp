/*
 *auto_ptr.cpp
 *cDate : 2013-9-28
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
#include <memory>
using namespace std;

/*解除引用运算符*及成员属性运算符-> */

class dog{
public:
    dog(){cout << "dog constructor.."<<endl;}
    ~dog() {cout << "dog destructor.."<<endl;}

    void Bark(){
        cout << " Bark Bark!..."<<endl;
    }
};

int main()
{
    /*相当于 int *int_ptr = new int;*/
    auto_ptr <int> int_ptr(new int);
    *int_ptr = 25;

    cout << "*int_ptr = " << *int_ptr << endl;
    
    /*相当于 dog * dog_ptr = new dog;*/
    auto_ptr <dog> dog_ptr(new dog);
    dog_ptr->Bark();
}



