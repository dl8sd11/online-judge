#include "linked-list.cpp"
 
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
}
 
void test2()
{
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
