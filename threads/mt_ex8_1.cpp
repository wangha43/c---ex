#include <mutex>  
#include <exception>  
#include <iostream>
#include <unistd.h>   
using namespace std;  
int main(){  
    mutex one,two;  
    try{  
        {  
            lock(one,two);  
            throw 1;  
            cout<<"locking..."<<endl;  
        }  
    }catch(int){  
        cout<<"catch..."<<endl;  
    }  
    sleep(2);
    if(!one.try_lock()&&!two.try_lock())  
        cout<<"failure"<<endl;  
    else  
        cout<<"success"<<endl;  
    return 0;  
}  