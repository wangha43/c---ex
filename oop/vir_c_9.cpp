#include <iostream>

#include <string.h>	


using namespace std;

template <typename T,int nSize>
class Butter
{
private:
	T m_attBuffer[nSize];

public :
	T *GetBuffer(){
		return m_attBuffer;
	}

	T & operator[](int nIndex){
		return m_attBuffer[nIndex];
	}
};

int main()
{
	Butter<int, 12> cIntBuffer;
 
    // Fill it up in order, then print it backwards
    for (int nCount=0; nCount < 12; nCount++)
        cIntBuffer[nCount] = nCount;
 
    for (int nCount=11; nCount >= 0; nCount--)
        std::cout << cIntBuffer[nCount] << " ";
    std::cout << std::endl;
 
    // declare a char buffer with room for 31 chars
    Butter<char, 31> cCharBuffer;
 
    // strcpy a string into the buffer and print it
    strcpy(cCharBuffer.GetBuffer(), "Hello there!");
    std::cout << cCharBuffer.GetBuffer() << std::endl;
	return 0;
}