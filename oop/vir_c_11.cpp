#include <iostream>
#include <map>
#include <string>
#include <functional>

void foo() { std::cout << "fo1o()"; }
void boo() { std::cout << "bo1o()"; }
void too() { std::cout << "to1o()"; }
void goo() { std::cout << "go1o()"; }

int main() {
		  std::map<std::string, std::function<void()>> functions;
		    functions["foo"] = foo;
			  functions["boo"] = boo;
			    functions["too"] = too;
				  functions["goo"] = goo;

				    std::string func;
					  std::cin >> func;
					    if (functions.find(func) != functions.end()) {
								    functions[func]();
									  }
						  return 0;
}
