/*
 *cast_operator.cpp
 *cDate : 2013-11-16
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*C++中的类型转换运算符
 * 基本格式：
 * type result = cast_type<type> (source);
 * */

/*static_cast:用于相关类型的指针之间的转换,还可显式地执行标准数据
 *类型的类型转换（这种转换将自动或隐式的进行）。用于指针时，static_cast
 *实现了基本编译阶段的检查，确保指针被转换为相关类型。
 *dynamic_cast:在运行阶段执行类型转换，可以检查dynamic_cast操作的结果
 *以判断类型的转换是否成功。
 *reinterpret_cast:是一种强制类型转换
 *const_cast: 是让程序员关闭对象的访问修饰符const。
 * */

class Animal{
public:
    //虚函数实现为空，不能被调用的。
    virtual void Speak() = 0;
};

class cDog: public Animal{
public:
    void WagTail(){
        cout << " Dog: i wagged my tail!" <<endl;
    }

    void Speak(){
        cout << " Dog: Bow...Bow..." << endl;
    }
};

class cCat: public Animal{
public:
    void CatchMice(){
        cout << "Cat: i caught a mouse!" << endl;
    }

    void Speak(){
        cout <<"Cat: Meow!" << endl;
    }
};

/*运行阶段判断对象的数据类型，并且调用各自的函数
 * */
void determinType(const Animal *pAnimal3)
{
    //const_cast 使用
    Animal *pAnimal = const_cast<Animal*>(pAnimal3);

    cDog *pDog = dynamic_cast<cDog*>(pAnimal);
    if(pDog){
        cout << "the Animal is a Dog!" << endl;
        pDog->WagTail();
    }

    cCat * pcat = dynamic_cast<cCat *>(pAnimal);
    if(pcat){
        cout << " the Animal is a Cat!" << endl;
        pcat->CatchMice();
    }
}

int main()
{
    Animal *pAnimal1 = new cDog();
    Animal *pAnimal2 = new cCat();
    double a = 78.12;
    double * pd = &a;

    //reinterpret_cast 强制类型转换使用
    //相当于 int *ch = (int *)pd
    int *ch = reinterpret_cast<int *>(pd);

    cDog *pDog = static_cast<cDog *>(pAnimal1);
    //cDog *pDog = static_cast<cDog *>(pAnimal2);
    //上面这句话会报错的，类型不匹配的

    //dynamic_cast 使用
    determinType(pAnimal1);
    determinType(pAnimal2);

    return 0;
}





        


