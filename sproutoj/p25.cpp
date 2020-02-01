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

/********** Main()  function **********/
struct Node{
    int data;
    Node *next;
};

class Queuee{
private:
  Node *head, *tail;
  int length;
public:
  Queuee(){
    head = NULL;
    tail = NULL;
    length = 0;
  }
  int size(){
    return length;
  }
  void push(int n){
    length++;
    Node *tmp = new Node;
    tmp->data = n;
    tmp->next = NULL;
    if(tail == NULL) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tmp;
    }


  }
  Node *getHead(){
    return this->head;
  }
  Node *getTail(){
    return this->tail;
  }
  int front(){
    return head->data;
  }
  void pop(){
    length--;
    Node *tmp = new Node;
    tmp = head;
    if (head == tail) {
      tail = tmp->next;
    }
    head = tmp->next;
    delete tmp;
  }
  void clear(){
    head = NULL;
    tail = NULL;
    length = 0;
  }
  void merge(Queuee *that){
    length += that->size();
    if (head==NULL) {
      head = that->getHead();
      tail = that->getTail();
      that->clear();
      return;
    }
    if(that->head == NULL) {
      return;
    }
    tail->next = that->getHead();
    tail = that->getTail();
    that->clear();
  }
  void printAll(){
    if(head==NULL) return;
    Node *it = new Node;
    it = head;
    while(it != tail){
      cout<<it->data<<' ';
      it = it->next;
    }
    cout<<it->data<<endl;
  }
};
int main()
{
  IOS();
  int n,m;
  cin>>n>>m;
  Queuee store[n];
  REP (u,m) {
    string cmd;
    cin>>cmd;
    if (cmd == "ADD") {
      int i,id;
      cin>>i>>id;
      store[i-1].push(id);
    } else if (cmd == "LEAVE") {
      int i;
      cin>>i;
      if(store[i-1].getHead()){
        store[i-1].pop();
      } else {
        cout<<"queue "<<i<<" is empty!"<<endl;
      }
    } else if (cmd == "JOIN") {
      int i,j;
      cin>>i>>j;
      store[j-1].merge(&store[i-1]);
      store[i-1].printAll();

    }
  }

  REP (i,n) {
    cout<<"queue "<<i+1<<": ";
    if(store[i].getHead()){
      store[i].printAll();
    } else {
      cout<<"empty"<<endl;
    }
  }
	return 0;
}
