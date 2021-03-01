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

int size = 0;
struct Node{
    int data;
    Node *left, *right, *par;
};
Node *root;
void insert(int n, Node *parent){
  if (parent) {
    if (n > parent->data) {
      if (parent->right) {
        insert(n,parent->right);
      } else {
        Node *tmp = new Node;
        tmp->data = n;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->par = parent;
        parent->right = tmp;
      }
    } else {
      if (parent->left) {
        insert(n,parent->left);
      } else {
        Node *tmp = new Node;
        tmp->data = n;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->par = parent;
        parent->left = tmp;
      }
    }
  } else {
    root = new Node;
    root->data = n;
    root->left = NULL;
    root->right = NULL;
    root->par = NULL;
  }
}
void query(int n){ //maybe ac
  Node *it = root;
  //if(!root)while(1){} no problem
  pair<int,int> ret;
  ret.X = root->data;
  ret.Y = root->data;
  while (it != NULL) {
    //if(!it->data)while(1){} no problem
    if (abs(it->data - n) < abs(ret.X - n)) {
      ret.X = it->data;
      ret.Y = it->data;
    } else if (abs(it->data - n) == abs(ret.X - n)) {
      ret.Y = it->data;
    }
    if (n > it->data) {
      it = it->right;
    } else {
      it = it->left;
    }
  }
  if (ret.X == ret.Y) {
    cout<<ret.X<<endl;
  } else {
    cout<<min(ret.X,ret.Y)<<' '<<max(ret.X,ret.Y)<<endl;
  }
}
void del(int n){
  Node *it = root;
  //if(!root)while(1){} no problem
  while(it!=NULL) {
    //if(!it->data)while(1){} no problem
    if (n > it->data) {
      it = it->right;
    } else if (n == it->data) {
      break;
    } else {
      it = it->left;
    }
  }
  // if (it == NULL) while(1){} TLE
  //if(root == it)debug("GOT");
  Node *leaf;
  if (it->right) {
    leaf = it->right;
    while(leaf->left){
      leaf = leaf->left;
    }
    it->data = leaf->data;
    if (leaf->right) {
      leaf->data = leaf->right->data;
      delete leaf->right;
      leaf->right = NULL;
    } else {
      if(leaf->par->left == leaf){
        leaf->par->left = NULL;
      } else {
        leaf->par->right = NULL;
      }

      delete leaf;
    }
  } else {
    if (it->par) {
      if (it->par->left == it) {
        it->par->left = it->left;
        delete it;
      } else {
        it->par->right = it->left;
        delete it;
      }
      if(it->left)it->left->par = it->par;
      if(it->right)it->right->par = it->par;
    } else {
      root = it->left;
      if(root){
        root->par = NULL;
      }


    }
  }

}
/********** Main()  function **********/
int main()
{
  IOS();
  int n;
  cin>>n;
  REP (i,n) {
    string cmd;
    cin>>cmd;
    int x;
    cin>>x;
    if (cmd == "insert") {
      insert(x,root);
    } else if (cmd == "query") {
      query(x);
    } else {
      del(x);
    }
    debug(root);
    if(root){
      debug(root->left);
      debug(root->right);
      debug(root->data);
      debug(root->par);
    }

    //debug("Done");
  }
	return 0;
}
