#include <iostream>        
#include <thread>        
#include <chrono>        
#include <mutex>        
int winner;
void set_winner(int x){winner = x;}
std::once_flag winner_flag;
void wait_1000ms (int id){
	for(int i = 0;i<1000;++i)
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	std::call_once(winner_flag,set_winner,id);
}
int main(int argc, char const *argv[])
{
	std::thread threads[10];
	for(int i = 0;i<10;++i){
		threads[i]=std::thread(wait_1000ms,i+1);
	}
	std::cout <<"waiting for the first among 10 threads"<<std::endl;
	for (auto& th : threads) th.join();  
  	std::cout << "winner thread: " << winner << '\n'; 
	return 0;
}