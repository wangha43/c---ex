#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
template <typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue(){}
	
	threadsafe_queue(threadsafe_queue const& other){
		std::lock_guard<std::mutex> lk(other.mut);
		data_queue=other.data_queue;
	}

	void push(T new_value){
		std::lock_guard<std::mutex> lk(mut);  
        data_queue.push(new_value);  
        data_cond.notify_one();
	}

	void wait_and_pop(T& value)
    {  
        std::unique_lock<std::mutex> lk(mut);  
        data_cond.wait(lk,[this]{return !data_queue.empty();});  
        value=data_queue.front();  
        data_queue.pop();  
    } 


}