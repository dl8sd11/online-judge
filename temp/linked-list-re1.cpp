#include <iostream>
#include <algorithm>
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
    void reverse();
};
 
 
LinkedList::LinkedList ()
{
    pHead=nullptr;
    pTail=nullptr;
}
 
LinkedList::LinkedList(int val)
{
    pHead=new Node(val);
    pTail=pHead; 
}
 
LinkedList::~LinkedList()
{
    Clear();
}
 
void LinkedList::TailAppend(int val)
{
    if (pHead==nullptr) {
        pHead=new Node(val);
        pTail=pHead;
    } 
    else
    {
        Node *Ntail = new Node(val);
        pTail->pNext = Ntail;
        pTail=Ntail;
    }
}
 
void LinkedList::HeadAppend(int val)
{
    if (pHead==nullptr) {
        pHead=new Node(val);
        pTail=pHead;
    } 
    else
    {
        Node *nhead = new Node(val);
        nhead->pNext=pHead;
        pHead=nhead;
 
    }
}
 
 
void LinkedList::Remove(int val)
{
    if (!pHead) return;
    Node *pFirst=pHead, *pRE = nullptr;
    while (pFirst && pFirst->value != val) {
        pRE=pFirst;
        pFirst=pFirst->pNext;
    }
    if (!pFirst) return;
    if (pFirst==pHead) {
        pHead = pHead->pNext;
        delete pFirst;
    } 
    else if (pFirst== pTail) {
        pTail = pRE;
        pTail->pNext = nullptr;
        delete pFirst;
    } 
    else {
        Node *pDEL=pFirst;
        pFirst=pFirst->pNext;
        pRE->pNext=pFirst;
        delete pDEL;
    }
}
 
void LinkedList::Clear()
{
    Node *ptr = pHead;
    while (ptr!=nullptr){
        Node *next = ptr->pNext;
        delete ptr;
        ptr = next;
    }
    pHead=nullptr;
    pTail=nullptr;
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
    int NUM=0;
    Node *ptrct=pHead;
    while(ptrct)
    {
        ptrct=ptrct->pNext;
        NUM++;
    }
 
    for (int i=0; i<NUM;i++){
        Node *A,*B, *C;
        A=nullptr;
        B=pHead;
        C=pHead->pNext;
        while (C) {
            if (B->value > C->value) {
                if (B== pHead) pHead=C;
                if (C== pTail) pTail =B;
                if (A) A->pNext = C;
                B->pNext=C->pNext;
                C->pNext = B;
                swap(B, C);
            }
            A=B;
            B=C;
            C=C->pNext;
        }
    }
 
 
}


void test1()
{
    LinkedList list;
    for (int i = 0 ; i < 10 ; i++)
    {
        list.TailAppend(-1 * i) ;
    }

    list.Print();
    list.BubbleSortList() ;
    list.Print();
    cout << "End test1" << endl;
}

void test2()
{
    cout << "Hello" << endl;
    LinkedList list2;
    for (int i = 0; i< 10; i++) {
        list2.TailAppend(i) ;
    }
    list2.Print();
}

void test3()
{
    LinkedList list2;
    for (int i = 510; i>= 500; i--) {
        list2.HeadAppend(i) ;
    }
    list2.Print();
}

void test4()
{
    LinkedList list2;
    for (int i = 0; i< 10; i++) {
        list2.TailAppend(i) ;
    }
    for (int i = 510; i< 520; i++) {
        list2.HeadAppend(i) ;
    }
    list2.Print();
    list2.Remove(31) ;
    list2.Print();
    list2.Remove(519) ;
    list2.Print();
    list2.Remove(5) ;
    list2.Print();
    list2.Remove(9) ;
    list2.Print();
    list2.BubbleSortList();
    list2.Print();
}


int main()
{
    test1();
    test2();
    test3();
    test4();
}

