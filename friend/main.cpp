#include "iostream"
using namespace std;
class Accumulator{
private:
    int m_value;
public:
    Accumulator() { m_value = 0; }
    void add(int value) { m_value += value; }
    int getvalue(){
        return m_value;
    }

    // Make the reset() function a friend of this class
    friend void reset(Accumulator &accumulator);
};
void reset(Accumulator &accumulator){
    //access to the private value
    accumulator.m_value = 0;
}

int main()
{
    Accumulator acc;
    acc.add(5);
    int a = acc.getvalue();
    cout << a <<endl;
    reset(acc);
    int b = acc.getvalue();
    cout <<b <<endl;
    return 0;
}

