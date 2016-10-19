#include <boost/thread/shared_mutex.hpp>  
#include <boost/thread/shared_lock_guard.hpp>  
#include <boost/thread.hpp>  
#include <iostream>  
using namespace std;  
typedef boost::shared_mutex rwmutex;  
typedef boost::shared_lock<rwmutex> readLock;  
typedef boost::unique_lock<rwmutex> writeLock;  
  
rwmutex m_mutex;  
void func1()  
{  
    writeLock lock1(m_mutex);  
    cout << "fffffffffffffff" << endl;  
}  
  
int main()  
{  
    {  
        boost::thread tt(func1);  
        readLock lock(m_mutex); // 
        {  
            sleep(3000);  // 
            readLock lock(m_mutex); //
            cout << "rrrrrrrrrrrrrrrrrr" << endl;  
        }  
    }  
}  