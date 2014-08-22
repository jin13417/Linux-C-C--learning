/*
 *virtual.cpp
 *Date : 2013-9-20
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*知识点：
 * 1、如何创建虚函数？
 *    在函数声明前加上virtual 关键字
 * 2、使用虚方法的意义
 *    基类中如果声明了虚方法，说明它的派生类中有可能会覆盖这个方法。
 * 3、如果在基类中将一个成员方法标记为虚方法，还需要在派生类中将它标记为虚方法吗？
 *    不需要，方法被声明为虚方法后，如果在派生类覆盖它，它仍是虚方法。在派生类继续
 *    将其标记为虚方法是个不错的主意，但是没有必要这么作，这样使代码更容易理解。
 * */

class Manmal {
public:
    Manmal():itsAge() { cout << "Manmal constrctor...\n";}
    virtual ~Manmal() { cout << "Manmal destructor...\n";}
    void Move() const { cout << "Manmal move one step\n";}
    virtual void Speak() const { cout << "Manmal speak!\n";}

protected:
    int itsAge;
};

class Dog :public Manmal{
public:
    Dog() { cout << " Dog constrctor...\n";}
    virtual ~Dog() { cout << " Dog destructor..\n";}
    void WagTail() { cout << " Wagging Tail...\n";}
    void Speak() const { cout << "Dog woof!\n";}
    void Move() const { cout << "Dog moves 5 steps ...\n";}
};

int main()
{
    /*创建一个信的dog对象，并返回该对象的指针，然后将该指针付给一个
     * Manmal指针。
     * 这是多态的本质，例如：可创建很多类型的窗口，包括对话框，可滚动
     * 窗库和列表框，然后给每种窗口定义一个虚方法draw().通过创建一个窗口指针，
     * 并将对话框和其他的派生对象赋給指针，就可以通过调用draw()，而不用考虑运行
     * 时指针只想的实际对象类型，程序将调用正确的draw()方法。
     * */

    Manmal *pDog = new Dog;
    pDog->Move();
    pDog->Speak();/*虚方法，被覆盖*/
    /*释放对象*/
    delete pDog;
    return 0;
}

