
/*
 *private_interitance.cpp
 *Date : 2013-9-20
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;
/*私有继承
 *基类的public protected 成员都以private身份出现在派生类中，但是基类
 *的private成员不可以访问。派生类的成员函数可以直接访问基类public protected
 *成员，但是不能访问积累的privated成员，派生类的对象不能访问基类的任何成员
 * */
/*基类：电动控制*/
class ElectricMotor{
public:
    ElectricMotor(){};
    virtual ~ElectricMotor(){};

public:
    void StartMotor(){
        Accelerate();
        Cruise();
    }

    void StopMotor(){
        cout << " Motor stopped" << endl;
    }

private:
    void Accelerate(){
        cout << " Motor started" << endl;
    }

    void Cruise(){
        cout << "Motor runnung at constant speed " << endl;
    }

};

/*派生类*/
#if 0
class Fan : private ElectricMotor{
public:
    Fan(){};
    virtual ~Fan(){};

    void StartFan(){
        StartMotor();
    }

    void StopFan(){
        StopMotor();
    }

};
#else
/*私有继承和聚合（组合）
 *
 * */
class Fan {
public:
    Fan(){};
    virtual ~Fan(){};

    void StartFan(){
        m_ElectricMotor.StartMotor();
    }

    void StopFan(){
       m_ElectricMotor.StopMotor();
    }
private:
    ElectricMotor m_ElectricMotor;

};

#endif

int main()
{
    Fan mFan;

    mFan.StartFan();
    mFan.StopFan();

    //mFan.Accelerate();
    //ElectricMotor * pmoto = &mFan;
    /*
    private_inheritance.cpp: In function ‘int main()’:
        private_inheritance.cpp:32: error: ‘void ElectricMotor::Accelerate()’ is private
        private_inheritance.cpp:65: error: within this context
        private_inheritance.cpp:65: error: ‘ElectricMotor’ is not an accessible base of ‘Fan’
        private_inheritance.cpp:66: error:
        */
}
            
            
        

