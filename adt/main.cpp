#include <QCoreApplication>
#include "bst.cpp"
int main()
{
BSTree<int> *bst = new BSTree<int>();
bst->Insert(3);
//bst->Insert(4);
//bst->Insert(5);
//bst->Insert(6);
//bst->Insert(-1);
//bst->Insert(1);
//bst->Insert(2);

delete bst;
return 0;
}

