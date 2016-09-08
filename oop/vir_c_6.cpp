#include <iostream>
#include <vector>
using namespace std;
void printStack(const vector<int> & stack){
		for(size_t i = 0 ; i < stack.size(); i++){
			int element = stack[i];
			cout <<element<<endl;
		}
		cout <<"cap : " <<stack.capacity() << " size :" << stack.size()<< endl;
}
int main(int argc, char const *argv[])
{
	std::vector<int> stack;
 
	printStack(stack);
 
	stack.push_back(5); // push_back() pushes an element on the stack
	printStack(stack);
 
	stack.push_back(3);
	printStack(stack);
 
	stack.push_back(2);
	printStack(stack);
 
	std::cout << "top: " << stack.back() << '\n'; // back() returns the last element
 
	stack.pop_back(); // pop_back() back pops an element off the stack
	printStack(stack);
 
	stack.pop_back();
	printStack(stack);
 
	stack.pop_back();
	printStack(stack);
	/* code */
	return 0;
}