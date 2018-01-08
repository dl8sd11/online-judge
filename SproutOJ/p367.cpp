#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(ll i=0;i<n;i++)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
typedef long long ll;
const ll MAXN = int(1e5) + 7;
ll n,m;
ll a[MAXN];
struct node {
    ll l,r;
    node *lc,*rc;
    ll d, da;
    node (ll li, ll ri, node *lci,node *rci,ll di,ll dai):l(li),r(ri),lc(lci),rc(rci),d(di),da(dai){}
};
node *build (ll l,ll r) {
    if (r==l+1) return new node(l,r,0,0,a[l],0);
    ll mid = (l+r)/2;
    node *tlc = build(l,mid);
    node *trc = build(mid,r);
    return new node(l,r,tlc,trc,max(tlc->d,trc->d),0);
}
ll query(ll l,ll r,node *now) {
    if (now->l==l&&now->r==r) return now->da+now->d;
    ll mid = (now->l+now->r)/2;
    if (r<=mid) return now->da+query(l,r,now->lc);
    if (l>=mid) return now->da+query(l,r,now->rc);
    else return now->da+max(query(l,mid,now->lc),query(mid,r,now->rc));
}
void mody(ll l,ll r, ll data,node *now) {
    if (now->l==l&&now->r==r) {
        now->da += data;
        return;
    }
    ll mid = (now->l+now->r)/2;
    if (r<=mid) {
        mody(l,r,data,now->lc);
        now->d = max(now->lc->da+now->lc->d,now->rc->da+now->rc->d);
        return;
    }
    if (l>=mid) {
        mody(l,r,data,now->rc);
        now->d = max(now->lc->da+now->lc->d,now->rc->da+now->rc->d);
        return;
    }
    mody(l,mid,data,now->lc);
    mody(mid,r,data,now->rc);
    now->d = max(now->lc->da+now->lc->d,now->rc->da+now->rc->d);
}
int main(){
    IOS();
    cin>>n>>m;
    REP (i,n) cin>>a[i];
    node *root = build(0,n);
    while (m--) {
        int cmd,x,y;
        cin>>cmd>>x>>y;
        if (cmd==1) {
            int add;
            cin>>add;
            mody(x-1,y,add,root);
        } else {
            cout<<query(x-1,y,root)<<endl;
        }
    }
}
