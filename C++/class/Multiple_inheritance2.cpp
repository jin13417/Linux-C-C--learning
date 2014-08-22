
/*
 *Multiple_interitance.cpp
 *Date : 2013-10-27
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>

#define N 0
using namespace std;

/*1、使用重载基类构造函数
 *2、避免歧义
 *
 */

typedef int HANDS;
enum COLOR{
    red,
    green,
    blue,
    yellow,
    white,
    black,
    brown
};



/*声明Horse 类*/
class Horse {
public:
    Horse(COLOR color,HANDS height):itsColor(color),itsWeight(height) { cout << "Horse constructor..." << endl;}
    virtual ~Horse() { cout << "Horse destructor..." << endl;}
    virtual void whinny() const { cout << "whinny!..." << endl;}
    virtual HANDS GetHeight() const {return itsWeight;}
    virtual COLOR GetColor() const {return itsColor;}
private:
    HANDS itsWeight;
    COLOR itsColor;
};

/*声明Bird类*/
class Bird {
public:
    Bird(COLOR color,HANDS height):itsColor(color),itsWeight(height) { cout << " Bird constructor..." << endl; }
    virtual ~Bird() { cout << "Bird destructor..." << endl; }
    virtual void Chirp() const { cout << "Chirp!..."<< endl; }
    virtual void Fly() const { 
        cout << " I can Fly! I can Fly!..."<<endl ;
    }
    virtual HANDS GetHeight() const {return itsWeight;}
    virtual COLOR GetColor() const { return itsColor;}
private:
    HANDS itsWeight;
    COLOR itsColor;
};

/*使用多重继承声明了Pegasus类*/
class Pegasus : public Horse,public Bird {
public:
    void Chirp() const {
        whinny();
    }
    Pegasus(COLOR color,HANDS wight,long numbelieve);
    ~Pegasus() { cout << " Pegasus destructor..." << endl ;}
    virtual long GetNumberBelievers() const {return itsNumberBelievers;}
#if N
    /*下面是另一种方法避免歧义 虚函数*/
    HANDS GetHeight()const {  return Bird::GetHeight();}
    COLOR GetColor()const { return Horse::GetColor();}
#endif

private:
    long itsNumberBelievers;
};

/*Pegasus 构造函数定义*/
Pegasus::Pegasus(COLOR color,HANDS wight,long numbelieve):Horse(color,wight),Bird(color,wight),itsNumberBelievers(numbelieve)
{
    cout << "Pegasus constructor..."<<endl;
}



/*分割线*/
void halving_line()
{
    cout << "*************************************************" << endl;
}


int main()
{
    Pegasus *pPeg = new Pegasus(red,5,10);
    pPeg->Fly();
    pPeg->whinny();

    cout << "Pegasus numbelieve  is " << pPeg->GetNumberBelievers() << endl;
#if  N
    cout << "Pegasus height  is " << pPeg->GetHeight() << endl;
    cout << "Pegasus color is " << pPeg->GetColor() << endl;
#else
/*上面2个打开，会发生多重歧义情况，因为在BirD，和HOrse 都带有2个函数的定义
 * 这个直接使用的话，程序不知道啊 会调用哪个。发生多重歧义
 *请参照下面的下法
 * */
   
    cout << "Pegasus height  is " << pPeg->Bird::GetHeight() << endl;
    cout << "Pegasus color  is " << pPeg->Horse::GetColor() << endl;
#endif

    delete pPeg;
    return 0;

}
