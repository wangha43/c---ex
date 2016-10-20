#include <atomic>
#include <memory>

template<typename T>
class lock_free_stack{
private:
	struct node {
		std::shared_ptr<T> data;
		node * next;
		node(T const & data_):data(std::make_shared<T>){data_}
	};
	std::atomic<node*> head;
public:
	void push(T const & data){
		node * const new_mode = new node(data);
		new_mode->next=head.load();
	}
}
