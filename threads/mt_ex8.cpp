#include <mutex>  
#include <iostream>  
using namespace std;  
mutex m;  
unique_lock<mutex> get_lock(){  
    unique_lock<mutex> lk(m);  
    cout<<"prepare data..."<<endl;//准备数据  
    return lk;//移动构造  
}  
int main(){  
    unique_lock<mutex> lk(get_lock());  
    cout<<"process data..."<<endl;//在mutex保护下数据深加工  
    return 0;  
}  