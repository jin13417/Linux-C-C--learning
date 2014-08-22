/*
 *class.cpp
 *Date : 2013-9-20
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*声明一个cat类
 * public private 修饰类的数据成员或方法成员
 * private:只能在类的方法中访问
 * public:可以通过类的任何对象进行访问
 * 默认情况下所有类型的成员都是私有的
 * 构造函数：constructor 创建并初始化类成员
 * 析构函数：destructor  对象被销毁后完成清理工作并释放分配的内存单元
 * 注意：一定要使用构造函数来初始化对象，添加构造函数后，一定要添加一个析构函数
 *      不要让构造函数和析构函数有返回值，不要让析构函数有参数
 */
class Cat {
private:
    int itsAge; //数据成员
public:
    Cat(int age); //构造函数
    ~Cat();//析构函数
    int GetAge() const; //方法成员const  表明类成员不能被修改
    void SetAge(int age);
    void Meow();
};

/*构造函数*/
Cat::Cat(int age)
{
    itsAge = age;
}

Cat::~Cat()
{
    cout << "something will cout" << endl;
}
    

/*析构函数*/

/*获得猫的年龄*/
int Cat::GetAge() const
{
    return itsAge;
}

/*设置类的名字*/
void Cat::SetAge(int age)
{
    itsAge = age;
}

void Cat::Meow()
{
    cout << "cat speak miao miao ...." << endl;
}

int main()
{
    Cat Frisky(10); //定义一个cat类
    cout << "Frisky.itsAge :" << Frisky.GetAge() << endl;
    Frisky.SetAge(5);
    cout << "SetAge(5)  Frisky.itsAge :" << Frisky.GetAge() << endl;
    Frisky.Meow();

    return 0;
}

    
