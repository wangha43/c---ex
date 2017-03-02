#include "iostream"
#include "cstdio"
#include "cstring"
#include "algorithm"
#include "cmath"
#include "utility"
#include "map"
#include "set"
#include "vector"

using namespace  std;
typedef long long ll;
const int MOD = 1e9+7;
enum ResultCode
{
    Underflow,
    Overflow,
    Success,
    duplicate,
    NotPresent
};

template <class T>
class DynamicSet
{
public:
    virtual ~DynamicSet();
    virtual ResultCode Search(T &x)const = 0;
    virtual ResultCode Insert(T &x) = 0;
    virtual ResultCode Remove(T &x) = 0;
};

template <class T>
struct BTNode
{
    BTNode()
    {
        lChild = rChild = NULL;
    }
    BTNode(const T &x)
    {
        element = x;
        lChild = rChild = NULL;
    }
    BTNode(const T &x,BTNode<T> *l,BTNode<T> *r)
    {
        element = x;
        lChild = l;
        rChild = r;
    }
    T element;
    BTNode<T> *lChild,*rChild;
};

template <class T>
class BSTree:public DynamicSet<T>
{
public:
    explicit BSTree(){ root = NULL;}
    virtual ~BSTree(){Clear(root);}
    ResultCode Search(T &x) const;
    ResultCode Search(T &x) const;
    ResultCode Insert(T &x);
    ResultCode Remove(T &x);
protected:
    BTNode<T> *root;
private:
    void Clear(BTNode<T> *t);
    ResultCode Search(BTNode<T> *p,T &x) const;
};

template <class T>
void BSTree<T>::Clear(BTNode<T> *t)
{
    if(t){
        Clear(t->lChild);
        Clear(t->rChild);
        cout <<"delete"<<t->element<<"..."<<endl;
        delete t;
    }
}

template <class T>
ResultCode BSTree<T>::search(T &x) const
{
    BTNode<T> *p = root;
    while(p){
        if(x<p->element) p = p->lChild;
        else if(x>p->element) p = p->rChild;
        else{
            x = p->element;
            return Success;
        }
        return NotPresent;
    }
//        return Search(root,x);
}

template <class T>
ResultCode BSTree<T>::Insert(T &x)
{
    BTNode<T> *p = root,*q = NULL;
    while(p){
        q=p;
        if(x<p->element) p = p->lChild;
        else if(x>p->element) p = p->rChild;
        else{
            x=p->element;
            return duplicate;
        }
    }
    p = new BTNode<T>(x);
    if(!root) root = p;
    else if(x<q->element)q->lChild = p;
    else q->rChild = p;
    return Success;
}

template <class T>
ResultCode BSTree<T>::remove(BTNode <T> *ro,T &x)
{
    BTNode <T> *c,*s,*r,*p = ro,*q = NULL;
    while(p && p->element != x){
        q=p;
        if(x<p->element) p = p->lChild;
        else p = p->rChild;
    }//find the position of x
    if(!p) return NotPresent;
    if(p->lChild ==NULL && p->rChild == NULL)
    {
        if(p == q->lChild)
            q->lChild =NULL;
        else
            q->rChild =NULL;
        delete p;
        return Success;
    }
    else if(p->lChild ==NULL){
        s=p;
        p=p->rChild;
        delete s;//delete pointer
        return Success;
    }
    else if(p->rChild==NULL){
        s=p;
        p=p->lChild;
        delete s;
        return Success;
    }
    else if(p->lChild && p->rChild){//two child
        c=p;
        while(c->lChild!=NULL){
            c = c->lChild;
        }
        p->element = c->element;
        remove(p->rChild,c->element);
    }
}


//template <class T>
//ResultCode BSTree<T>::Search(BTNode<T> *p,T &x) const
//{
//    if(!p) return NotPresent;
//    if(x<p->element) return Search(p->lChild,x);
//    if(x>p->element) return Search(p->rChild,x);
//    x=p->element;
//    return Success;
//}


