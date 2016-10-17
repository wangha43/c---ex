#include<iostream>  
#include<boost/thread.hpp>  
#include<boost/shared_ptr.hpp>  
using namespace std;  
class test{  
    public:  
        test(int i=0):data(i){}  
        ~test(){  
            cout<<"test::destructor"<<endl;  
        }  
        test(const test& one){  
            data=one.data;  
        }  
        test& operator=(const test& one){  
            data=one.data;  
            return *this;  
        }  
    public:  
        int data;  
};  
void fun(boost::shared_ptr<test> ptr){  
    ptr->data++;  
}  
void fun_(test* ptr){  
    ptr->data++;  
}  
void oops(){  
    boost::shared_ptr<test> ptr(new test(10));  
    boost::thread my_thread(fun,ptr);  
    my_thread.join();  
    cout<<"shared_ptr "<<ptr->data<<endl;  
    test* one=new test(10);  
    boost::thread t(fun_,one);  
    t.join();  
    cout<<"test* "<<one->data<<endl;  
    delete one;  
}  
int main(){  
    oops();  
    return 0;  
}  