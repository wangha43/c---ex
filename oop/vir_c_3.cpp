#include <iostream>
using namespace std;
class Base
{
public:
    Base(){
        cout << "Base::Base()" <<endl;
    }
   virtual ~Base()
    {
        cout << "Calling ~Base()" << endl;
    }
};
 
class Derived: public Base
{
private:
    int* m_pnArray;
 
public:
    Derived(int nLength)
    {
        cout << "Derived::Derived()" <<endl;
        m_pnArray = new int[nLength];
    }
 
    ~Derived() // note: not virtual
    {
        cout << "Calling ~Derived()" << endl;
        delete[] m_pnArray;
    }
};

//deconstructors
int main()
{
    // Derived *pDerived = new Derived(5);
    // Base *pBase = pDerived;
    Base *pBase = new Derived(5);
    delete pBase;
/*------------------the result is ----------------------*/ 
//Calling ~Derived()
//Calling ~Base()

    return 0;
}