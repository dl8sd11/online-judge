#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const ll MAXN = 100003;
ll n,m,tmp;
vector<ll> ans;
struct node{
  ll pri,val,si;
  node *l, *r;
  node(ll x){
    pri = rand();
    l = r = 0;
    si = 1;
    val = x;
  }
  void pull(){
    ll ret = 0;
    if(l) ret += l->si;
    if(r) ret += r->si;
    si = ret + 1;
  }
};
ll SI(node *nd){return nd?nd->si:0;}
node *root = NULL;
node *merge(node *a,node *b){
  if(!a||!b)return a?a:b;
  if(a->pri > b->pri){
    a->r = merge(a->r,b);
    a->pull();
    return a;
  } else {
    b->l = merge(a,b->l);
    b->pull();
    return b;
  }
}
void split(node *s,ll k,node *& a,node *& b){
  if(!s) a = b = 0;
  else if(k==0) b = s,a=0;
  else if(k==SI(s)) a = s,b=0;
  else if (SI(s->l) < k) {
    a = s;
    split(s->r,k-SI(s->l)-1,a->r,b);
    a->pull();
  } else {
    b = s;
    split(s->l,k,a,b->l);
    b->pull();
  }
}
void insert(ll k){
  root = merge(root,new node(k));
}
void push_treap(node *nd){
  if(nd->l)push_treap(nd->l);
  ans.push_back(nd->val);
  if(nd->r)push_treap(nd->r);
}
int main(){
  cin>>n>>m;
  for(int i=1;i<=n;i++) {
    cin>>tmp;
    insert(tmp);
  }
  ll q,i,j;
  while(m--){
    cin>>q>>i>>j;
    if(q==1){
      node *a,*b,*c;
      split(root,i-1,a,b);
      split(b,j-i+1,b,c);

      root = merge(b,merge(a,c));
    }else{
      node *a,*b,*c;
      split(root,i-1,a,b);
      split(b,j-i+1,b,c);
      root = merge(a,merge(c,b));
    }
  }
  push_treap(root);
  cout<<abs(ans.back()-ans.front())<<endl;
  for(auto v:ans)cout<<v<<' ';
  cout<<endl;
}
