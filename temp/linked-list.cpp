#include <iostream>
using namespace std;
 
class Node
{
    friend class LinkedList ;
private :
 
    int      value ;
    Node     *pNext;
 
public :
    Node () : pNext (NULL) {}
    Node (int val) :value (val) , pNext (NULL) {}
    Node (int val,Node *next) : value (val) , pNext (next) {}
};
 
 
class LinkedList
{
private:
    Node * pHead ;
    Node * pTail ;
 
public :
    LinkedList() ;
    LinkedList(int val) ;
    ~LinkedList() ;
 
    void TailAppend(int val);
    void HeadAppend(int val);
    void Clear();
    void Print();
    void BubbleSortList();
    void Remove(int val);
};

 
LinkedList::LinkedList ()
{
    pHead = pTail = nullptr;
}
 
LinkedList::LinkedList(int val)
{
    pHead = pTail = new Node(val);
}
 
LinkedList::~LinkedList()
{
    Clear();
}

void LinkedList::TailAppend(int val)
{
    if (!pHead) {
        pHead = pTail = new Node(val);
    } else {
        Node *new_tail = new Node(val);
        pTail->pNext = new_tail;
        pTail = new_tail;
    }
}
 
void LinkedList::HeadAppend(int val)
{
    if (!pHead) {
        pHead = pTail = new Node(val);
    } else {
        Node *new_head = new Node(val, pHead);
        pHead = new_head;
    }
}
 
 
void LinkedList::Remove(int val)
{
    if (!pHead) return;
    Node *cur = pHead, *prv = nullptr;
    while (cur && cur->value != val) {
        prv = cur;
        cur = cur->pNext;
    }
    if (cur == pHead) {
        pHead = cur->pNext;
        delete cur;
    } else if (cur == pTail) {
        pTail = prv;
        pTail->pNext = nullptr;
        delete cur;
    } else if  (cur) {
        prv->pNext = cur->pNext;
        delete cur;
    }
}
 
void LinkedList::Clear()
{
    Node *ptr = pHead;
    while (ptr) {
        Node *nxt = ptr->pNext;
        delete ptr;
        ptr = nxt;
    }
    pHead = pTail = nullptr;
}
 
void LinkedList::Print()
{
    Node *p = pHead ;
    if (pHead == NULL)
    {
        cout << "This list is empty"<<endl ;
        return ;
    }
    cout << "LinkedList : ";
 
    while (p!= NULL)
    {
        cout <<p->value << " " ;
        p = p->pNext ;
    }
    cout << endl ;
 
}
 
 
void LinkedList::BubbleSortList()
{
    if (pHead == pTail) return;

    int length = 0;
    for (Node *ptr=pHead; ptr; ptr=ptr->pNext, length++);

    for (int i=0; i<length; i++) {
        Node *prv = nullptr, *cur=pHead, *nxt=pHead->pNext;
        while (nxt) {
            if (cur->value > nxt->value) {
                if (cur == pHead) {
                    pHead = nxt;
                }
                if (nxt == pTail) {
                    pTail = cur;
                }
                if (prv) prv->pNext = nxt;
                cur->pNext = nxt->pNext;
                nxt->pNext = cur;
                swap(cur, nxt);
            }
            prv  = cur;
            cur = nxt;
            nxt = nxt->pNext;
        }
    }


}


