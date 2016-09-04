#include <iostream>
#include <string>
using namespace std;
class Animal
{
protected:
    std::string m_strName;
 
public:
    Animal(std::string strName)
        : m_strName(strName){}
 
    std::string GetName() { return m_strName; }
    virtual const char* Speak() = 0; // pure virtual function
};
class Cow : public Animal{
public:
    Cow(std::string strName)
        : Animal(strName)
    {
    }

    virtual const char* Speak() { return "Moo"; }
};
 int main(){
      Cow cCow("Betsy");
    cout << cCow.GetName() << " says " << cCow.Speak() << endl;
 }