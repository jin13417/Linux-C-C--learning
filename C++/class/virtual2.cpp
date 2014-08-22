/*
 *virtual2.cpp
 *Date : 2013-9-20
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*依次调用多个虚方法。
 * */

class Manmal {
public:
//    Manmal():itsAge() { cout << "Manmal constrctor...\n";}
  //  virtual ~Manmal() { cout << "Manmal destructor...\n";}
    virtual void Speak() const { cout << "Manmal speak!\n";}

protected:
    int itsAge;
};
class Dog :public Manmal{
public:
    void Speak() const { cout << "Dog woof!\n";}
};

class cat :public Manmal{
public:
    void Speak() const { cout << "cat Meow!\n";}
};

class Horse :public Manmal{
public:
    void Speak() const { cout << "Horse Winnie!\n";}
};

class Pig :public Manmal{
public:
    void Speak() const { cout << "Dog Qink!\n";}
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

    Manmal * theArray[5] = {NULL};
    Manmal * ptr;
    int choice ,i;

    for(i = 0; i<5; i++){
        cout << "1) Dog 2) cat 3) Horse 4) Pig 请输入：";
        cin >> choice;
        switch(choice){
            case 1: ptr = new Dog;   break;
            case 2: ptr = new cat;   break;
            case 3: ptr = new Horse; break;
            case 4: ptr = new Pig;   break;
            default:ptr = new Manmal;break;
        }
        theArray[i] = ptr;
    }
    for(i=0;i<5;i++){
        theArray[i]->Speak();
        delete theArray[i];
    }
    return 0;
}

