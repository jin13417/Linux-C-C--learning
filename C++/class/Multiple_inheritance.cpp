

/*
 *Multiple_interitance.cpp
 *Date : 2013-10-20
 *Author: sjin
 *Mail:413977243@qq.com
 */
#include <iostream>
using namespace std;

/*声明Horse 类*/
class Horse {
public:
    Horse() { cout << "Horse constructor..." << endl;}
    virtual ~Horse() { cout << "Horse destructor..." << endl;}
    virtual void whinny() const { cout << "whinny!..." << endl;}
private:
    int itsAge;
};

/*声明Bird类*/
class Bird {
public:
    Bird() { cout << " Bird constructor..." << endl; }
    virtual ~Bird() { cout << "Bird destructor..." << endl; }
    virtual void Chirp() const { cout << "Chirp!..."<< endl; }
    virtual void Fly() const { 
        cout << " I can Fly! I can Fly!..."<<endl ;
    }
private:
    int itsWeight;
};

/*使用多重继承声明了Pegasus类*/
class Pegasus : public Horse,public Bird {
public:
    void Chirp() const {
        whinny();
    }
    Pegasus() {cout << " Pegasus constructor..." << endl ;}
    ~Pegasus() { cout << " Pegasus destructor..." << endl ;}
};

/*help*/

void help(int * choice,int flag)
{
    if(flag == 1){
        cout << " (1) Horse (2) Pegasus:";
    }else {
        cout << " (1) Bird (2) Pegasus:";
    }
        
    cin >> *choice;
}

/*分割线*/
void halving_line()
{
    cout << "*************************************************" << endl;
}

const int MagicNumber = 2;

int main()
{
    // Ranch:牧场；Aviary:鸟舍
    Horse *Ranch[MagicNumber];
    Bird * Aviary[MagicNumber];

    Horse * pHorse;
    Bird * pBird;

    int choice,i;
    halving_line();
    for(i = 0; i<MagicNumber; i++){
         help(&choice, 1);
         if(choice == 2){
             pHorse = new Pegasus;
         }else{
             pHorse = new Horse;
         }

         Ranch[i] = pHorse;
    }
    halving_line();
    for(i = 0; i < MagicNumber; i++){
        help(&choice,2);
        if(choice == 2){
            pBird = new Pegasus;
        }else{
            pBird = new Bird;
        }
        Aviary[i] = pBird;
    }
    halving_line();

    for(i = 0;i < MagicNumber; i ++){
        cout << "牧场：" << endl;
        Ranch[i]->whinny();
        delete Ranch[i];
    }


    for(i = 0;i < MagicNumber; i ++){
        cout << "鸟舍：" << endl;
        Aviary[i]->Chirp();
        Aviary[i]->Fly();
        delete Aviary[i];
    }

    return 0;
}

