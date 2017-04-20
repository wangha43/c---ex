#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
/*
 *线程循环 10 次，接着主线程循环 100 次，接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次，如此循环50次
 */
mutex m;
condition_variable cond;
int flag =10;
void fun(int num){
	for(int i=0;i<50;i++){  
        unique_lock<mutex> lk(m);//A unique lock is an object that manages a mutex object with unique ownership in both states: locked and unlocked.  
        while(flag!=num)  
            cond.wait(lk);//wait for notify
        for(int j=0;j<num;j++)  
            cout<<j<<" ";  
        cout<<endl;  
        flag=(num==10)?100:10;  
        cond.notify_one();//被阻塞的线程唤醒后lk.lock()恢复在调用wait前的状态  
    } 
}
int main()
{
	/* code */
	thread child(fun,10);
	fun(100);
	child.join();
	return 0;
} 