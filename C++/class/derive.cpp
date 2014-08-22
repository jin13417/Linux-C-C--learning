
/*
 *derive.cpp
 *Date : 2013-9-24
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
#define N 1


using namespace std;

/*三种访问限定符：
 * 公有（public),保护（protected)和私有（private)
 *  如果在函数中声明了一个对象，则它可以访问所有的共有成员
 *  数据和函数。而成员函数可以访问其所属类的私有数据成员和
 *  函数。也可以访问任何从其所属类派生而来的类的保护数据成员
 *  和函数。
 */
/*定义一个枚举类型结构*/
enum BREED{
    GOLDEN,
    CAIRN,
    DANDIE,
    SHETLAND,
    DOBERMAN,
    LAB
};

class Manmal{
public:
    Manmal():itsAge(2),itsWeight(5){ cout << " create Manmal object..."<<endl;}
    ~Manmal(){cout << " destroy Manmal object..."<<endl;}
    
    /*inline 函数写法*/
    int GetAge()const{ return itsAge;}
    void SetAge(int age){itsAge = age;}
    int GetWeight()const{ return itsWeight;}
    void SetWeight(int weight){itsWeight = weight;}

    //other methods
    void Speak()const { cout << "Manmal sound!\n";}
    void Sleep()const { cout << "shh,I am Sleeping.\n";}

private:
    int itsAge;
    int itsWeight;
};

class Dog : public Manmal {
public:
    Dog():itsBread(GOLDEN){cout << " create Dog object..." << endl;}
    ~Dog(){cout << " destroy Dog object..."<< endl;}

    BREED GetBread() const {return itsBread;}
    void SetBread(BREED breed) { itsBread = breed;}

    void WagTail() const { cout << "Tail wagging..\n";}
    void BegForFood() const { cout << "Begging for food..\n";}
#if N
   /*这里将覆盖基类的函数Speak（）
    *派生类中覆盖基类函数，意味者在派生类中重写了函数的实现
    *在派生类中创建一个返回值和特征标和基类成员函数相同但是实现
    *不同的函数时，被成为覆盖该函数。
    *注意：
    *    在覆盖函数时，特征标必须和基类中被覆盖的函数相同。（这里特征标指的是
    *    函数原型中除返回类型以外的内容，函数名，参数列表和可能用到的关键字const
    * */

    void Speak()const { cout << "Dog sound!\n";}
#endif
private:/*私有类型，只能有内部补函数调用*/
    BREED itsBread;

};
/*Manmal类是基类，Dog类是Manmal类的派生类
 * 所有的dog对象都有年龄、体重和品种。是从Manmal类继生而来的
 * */

int main()
{
    /*声明一个dog对象：Fido,它继承了Manmal的所有属性，同时具有
     * Dog的所有属性。*/
    Dog Fido;
    Fido.Speak();/*当N 为0时，将输出基类的Speak()函数*/
    Fido.WagTail();
    cout << "Fido is "<< Fido.GetAge() << "years old" << endl;
    cout << "N is:\t" << N << endl;
#if N
    cout << "**********覆盖基类的函数***********" << endl;
    Manmal pMan;
    cout << "基类的Speak()方法：";
    pMan.Speak();
    cout << "派生类的speak()方法：";
    Fido.Speak();
#endif
    return 0;
}

