#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<ll, ll> pi;
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll INF = (ll)1e18 + 7;
const ll MOD = 1000000007;

struct Node{
  int data;
  Node *prev, *next;
};
class Linked_List{
private:
  Node *head, *tail;
public:
  Linked_List(){
    head = NULL;
    tail = NULL;
  }
  Node *push_back(int n) {
    Node *tmp = new Node;
    tmp->data = n;
    tmp->next = NULL;
    if (head == NULL) {
      head = tmp;
      tmp->prev = NULL;
    } else {
      tail->next = tmp;
      tmp->prev = tail;
    }
    tail = tmp;
    return tmp;
  }
  void pop(Node *p2) {
    if (head == tail) {
      Node *tmp = head;
      delete tmp;
      head = NULL;
      tail = NULL;
      return;
    }
    Node *p1 = p2->prev;
    Node *p3 = p2->next;
    if (p1) {
      p1->next = p3;
    } else {
      head = p3;
    }
    if (p3) {
      p3->prev = p1;
    } else {
      tail = p1;
    }
    delete p2;
  }
  void swap(Node *p3){
    debug(p3);
    if (p3 == head) {
      return;
    }
    debug(p3);
    Node *p2 = p3->prev;
    Node *p4 = p3->next;
    Node *p1 =  p2->prev;
    p3->next = p2;
    p2->prev = p3;
    if (p4) {
      p2->next = p4;
      p4->prev = p2;
    } else {
      p2->next = NULL;
      tail = p2;
    }

    if (p1){
      p3->prev = p1;
      p1->next = p3;
    } else {
      debug(p3);
      p3->prev = NULL;
      head = p3;
      debug(head);
    }

  }
  void printElement(){
    if (head == NULL) return;
    Node *it = head;
    while (it != tail) {
      cout<<it->data<<' ';
      it = it->next;
    }
    cout<<it->data<<endl;
  }
};
/********** Main()  function **********/
int main()
{
  IOS();
  Linked_List li;


  int n,m;
  cin>>n>>m;
  Node *ptr[n];
  REP(i,n) {
    ptr[i] = li.push_back(i+1);
  }
  REP (i,m) {
    int cmd,x;
    cin>>cmd>>x;
    if (cmd == 0) {
      li.pop(ptr[x-1]);
    } else {
      li.swap(ptr[x-1]);
    }
  }
  li.printElement();
	return 0;
}
