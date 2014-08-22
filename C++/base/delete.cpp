//using new and delete
#include <iostream>

using namespace std;

class Simplecat{
    public:
        Simplecat();
        ~Simplecat();
    private:
        int itsAge;
};

Simplecat::Simplecat()
{
    cout << "Constructor called ******" << endl;
    itsAge = 1;
}

Simplecat::~Simplecat()
{
    cout << "Destructor called." << endl;
}

int main()
{
    cout << "Simplecat Frisky******start *****"<< endl;
    Simplecat Frisky;
    cout << "Simplecat Frisky******end******"<< endl;
    
    cout <<"new  Simplecat*******start******"<< endl;
    Simplecat *ptags = new Simplecat;
    delete ptags;
    cout << "new Simplecat******end******"<<endl;

    return 0;
}

