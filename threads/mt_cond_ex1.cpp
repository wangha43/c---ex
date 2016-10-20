#include <unistd.h>
#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static const int kItemRepositorySize =10;
static const int kItemToProduce = 1000;

struct ItemRepository
{
	int item_buffer[kItemRepositorySize];
	size_t read_position;
	size_t write_position;
	std::mutex mtx;
	std::condition_variable repo_not_full;
	std::condition_variable repo_not_empty;
}gItemRepository;

typedef struct ItemRepository ItemRepository;

void ProduceItem(ItemRepository *ir,int item){
	std::unique_lock<std::mutex> lock(ir->mtx);
	while(((ir->write_position + 1)%kItemRepositorySize)
		== ir->read_position){
		std::cout <<"waiting for a empty slot"<<std::endl;
		(ir->repo_not_full).wait(lock);
	}

	(ir->item_buffer)[ir->write_position]=item;
	ir->write_position++;

	if(ir->write_position == kItemRepositorySize)
		ir->write_position = 0;

	ir->repo_not_full.notify_all();
	lock.unlock();
}

int ConsumerItem(ItemRepository * ir){
	int data;
	std::unique_lock<std::mutex> lock(ir->mtx);

	while(ir->write_position == ir->read_position){
		std::cout << "consumer is waiting for items...\n";
		(ir->repo_not_empty).wait(lock);
	}

	data = (ir->item_buffer)[ir->read_position];

	if(ir->read_position >=kItemRepositorySize)
		ir->read_position = 0;

	(ir->repo_not_full).notify_all();

	lock.unlock();

	return data;
}

void ProducerTask(){
	for (int i = 0; i <=kItemToProduce; ++i)
	{
		std::cout << "Produce the "<<i <<"^th item..."<<std::endl;
		ProduceItem(&gItemRepository,i);
	}
}

void ConsumerTask(){
	static int cnt = 0;
	while(1){
		sleep(1);
		int item = ConsumerItem(&gItemRepository);
		std::cout << "Consumer the "<<item <<"^th item"<<std::endl;
		if(++cnt == kItemToProduce) break;
	}
}

void InitItemRepository(ItemRepository *ir){
	ir->write_position = 0;
	ir->read_position = 0;
}

int main(int argc, char const *argv[])
{
	InitItemRepository(&gItemRepository);
	std::thread producer(ProducerTask);
	std::thread consumer(ConsumerTask);
	producer.join();
	consumer.join();
	return 0;
}