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

struct node{
  int x;
  node *next;
};
class LinkList {
private:
  node *head,*tail;
public:
  LinkList(){
    head = NULL;
    tail = NULL;
  }
  int top(){
    // if(head == NULL){
    //   while(1){debug("fail");}
    // }
    return head->x;
  }
  // int size(){
  //   // if size() == 0 head always equals tail (V)
  //   if (head == NULL && tail == NULL) return 0;
  //    //if (head == NULL || tail == NULL) while(1){}
  //   else {
  //     node *it = new node;
  //     it = head;
  //     int ret = 0;
  //     while(it!=tail) {
  //       ret++;
  //       it = it->next;
  //     }
  //     return ret+1;
  //   }
  //
  // }
  node *getHead(){
    return head;
  }
  void pop_front(){
    //it never happen while size() == 0
    //if(!size())while(1){}
    node *tmp = new node;
    tmp = head;
    if(tail == head) {
      tail = tmp->next;
    }
    head = head->next;

    delete tmp;

  }
  node *insert(node *current,int n){
    // warning head and tail isn't always exist
    //if(!head||!tail)while(1){}
    //current is always !NULL
    if (current == tail) {
      node *ret = new node;
      ret = pb(n);
      return ret;
    }
    //int ts =
    //sometimes this doesn't work properly
    node *tmp = new node;
    tmp->x = n;
    tmp->next = current->next;
    current->next = tmp;
    //if(current == head && size() - ts == 0 ) while(1){}

    return tmp;
  }
  // void displayAll(){
  //
  //   node *current = new node;
  //   current = head;
  //   cout<<'{';
  //   while(current != tail) {
  //     cout<<current->x<<',';
  //     current = current->next;
  //   }
  //   cout<<current->x<<'}'<<endl;
  //
  // }
  node *push_back(int n){
    //it always work
    //int ts = size();
    node *tmp = new node;
    tmp->x = n;
    tmp->next = NULL;
    if (head == NULL) {
      head = tmp;
      tail = tmp;
    } else {
      tail->next = tmp;
      tail = tail->next;
    }
    //if(size() - ts != 1)while(1){}
    return tmp;
  }
};
/********** Main()  function **********/
int main()
{
  IOS();
  int cnt = 0;
  int n;
  while (cin>>n) {
    int cn[1000000] = {};
    LinkList lt;
    REP1 (i,n) {
      int k;
      cin>>k;
      REP (j,k) {
        int tmp;
        cin>>tmp;
        cn[tmp] = i;
      }
    }
    debug(cn); //check input of China people
    cout<<"Line #"<<++cnt<<endl;
    string cmd;
    cin>>cmd;
    node *last[n] = {};
    //the {} to pointer array is safe
    //REP(i,n) if(last[i])while(1){}
    while (cmd != "STOP") {
      if (cmd == "ENQUEUE") {
        //int ts = lt.
        int p;
        cin>>p;
        int gp = cn[p];
        if (gp==0) {
          lt.pb(p);
        } else {
          if(last[--gp]) {
            //if(!lt.size())while(1){}
            last[gp] = lt.insert(last[gp],p);
            //if(lt.size()-ts == 0)while(1){}
          } else {
            last[gp] = lt.pb(p);
          }
        }

      } else if (cmd == "DEQUEUE") {

        cout<<lt.top()<<endl;
        int gp = cn[lt.top()];
        if(last[--gp] == lt.getHead()){
          last[gp] = NULL;
        }
        lt.pop_front();
      }
      cin>>cmd;
    }
  }

	return 0;
}
