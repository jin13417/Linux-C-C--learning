/*
 *derive2.cpp
 *Date : 2013-9-24
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
#define N 0


using namespace std;

/*知识点：
 * 1、隐藏基类的方法（就是在派生类中重新实现函数的定义）
 * 2、当基类的方法被覆盖时，仍可诶通过限定方法名来调用它，如下格式：
 *    baseclass::Method();
 */

/*基类*/
class Manmal{
public:
    //Manmal():itsAge(2),itsWeight(5){ cout << " create Manmal object..."<<endl;}
    //~Manmal(){cout << " destroy Manmal object..."<<endl;}
    
    void Move() const { cout << "Manmal move one step..." << endl;}
    void Move(int distance) const
    {
        cout << "Manmal Move '" << distance << "' steps..." << endl;
    }

private:
    int itsAge;
    int itsWeight;
};

/*派生类*/
class Dog : public Manmal {
public:
    //Dog() {cout << " create Dog object..." << endl;}
    //~Dog() {cout << " destroy Dog object..."<< endl;}

    /*隐藏了基类的Move()方法*/
    void Move() const 
    { 
        cout << "Dog move 5 steps..." << endl;
        cout << "隐式调用基类方法(start):" << endl;
        Manmal::Move();
        Manmal::Move(1000);
        cout << "隐式调用基类方法(end):" << endl;
    }

};

int main()
{
    Manmal bigAnimal;
    Dog Fido;
    cout << "**********Manmal bigAnimal*************" << endl;
    bigAnimal.Move();
    bigAnimal.Move(2);
    cout << "**********Dog Fido*************" << endl;
    Fido.Move();
    //Fido.Move(2);
    /* 上面将会出现下面的错误
     * derive2.cpp:56: error: no matching function for call to ‘Dog::Move(int)’
     * derive2.cpp:43: note: candidates are: void Dog::Move() const
     * 也就是说： 覆盖任一个重载的方法后，该方法的其他所有版本都会被隐藏。
     *            如果补希望他们被隐藏，必须对其进行覆盖。
     */
    
    /*显式调用被隐藏基类的方法*/
    cout << "显式调用基类方法(start):" << endl;
    Fido.Manmal::Move();
    Fido.Manmal::Move(200);
    cout << "显式调用基类方法(end):" << endl;
     

}

