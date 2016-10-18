#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
using namespace std;

struct bank_account{
	explicit bank_account(string iname,int money){
		name = iname;
		iMoney = money;
	}
	string 	name;
	int iMoney;
	mutex mMutex;
};

void transfer(bank_account & from_account,bank_account & to_account,int amount){
	unique_lock<mutex> lock1(from_account.mMutex,defer_lock);
	unique_lock<mutex> lock2(to_account.mMutex,defer_lock);
	lock(lock1,lock2);
	from_account.iMoney -= amount;
	to_account.iMoney += amount;
	cout << "Transfer " << amount << " from "<< from_account.name << " to " << to_account.name << endl;  
}

int main()
{
	/* code */
	bank_account Account1( "User1", 100 );  
  	bank_account Account2( "User2", 50 );
  	thread t1([&](){transfer(Account1,Account2,10);});
  	thread t2([&](){transfer(Account2,Account1,5);});  
  	t1.join();
  	t2.join();
  	cout << Account1.iMoney<<endl;
  	cout << Account2.iMoney<<endl;
	return 0;
}