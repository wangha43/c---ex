#ifndef linkedlist_h
#define linkedlist_h
#include <iostream>
#include <string>

using namespace std;
/*
 *node struct contain data and a pointer to the next node
 *
 */

struct node
{
	string song;
	string artist;
	node * next;
};

/*
 *linkedlist is a list of linked nodes
 */
class linkedlist{
private:
	node * head;
	int listLength;
public:
	linkedlist();
	bool insertNode(node * newnode,int position);
	bool removeNode(int position);
	void printList();
	~linkedlist();
};

#endif