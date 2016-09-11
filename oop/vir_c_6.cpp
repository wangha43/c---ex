#include <iostream>
#include <cstdlib>

int main()
{
	using namespace std;
	cout << "Enter your age:"<<endl;
	int nAge;
	cin >>nAge;
	if(nAge<=0){
		cerr<< "Oops , you entered a invalid number" <<endl;
		exit(1);
	}
	cout << "you entered "<<nAge<<endl;
	return 0;
}	