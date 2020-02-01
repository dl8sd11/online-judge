#include <bits/stdc++.h>
using namespace std;
typedef int ll;

const ll MOD = 1000000007;
const ll MAXN = 500003;
const ll K = 700;

struct Query {
    ll l,r,lid,qid;
    bool operator < (const Query &q1) const{
        if (lid != q1.lid) {
            return lid < q1.lid;
        } else {
            return (lid&1) ? (r>q1.r) : (r<q1.r);
        }
    }
}query[MAXN];

ll cnt[MAXN];
ll n,a[MAXN],q,ans[MAXN];
bool inv[MAXN];
vector<ll> one;

__attribute__((always_inline)) void upd(ll val) {
    if (cnt[val]==1&&!inv[val]) {
        one.emplace_back(val);
        inv[val] = true;
    }
}
__attribute__((always_inline)) void add(ll val) {
    cnt[val]++;
    upd(val);
}

__attribute__((always_inline)) void sub(ll val) {
    cnt[val]--;
    upd(val);
}


void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

/********** Good Luck :) **********/
int main()
{
    read(n);
    for (ll i=0;i<n;i++) {
        read(a[i]);
    }
    read(q);
    for (ll i=0;i<q;i++) {
        read(query[i].l);
        read(query[i].r);
        query[i].l--;
        query[i].r--;
        query[i].lid = query[i].l / K;
        query[i].qid = i;
    }
    sort(query,query+q);

    ll L = 0,R = -1;
    for (ll i=0;i<q;i++) {
        while (R < query[i].r) {
            ++R;
            add(a[R]);
        }
        while (R > query[i].r) {
            sub(a[R]);
            --R;
        }
        while (L > query[i].l) {
            --L;
            add(a[L]);
        }
        while (L < query[i].l) {
            sub(a[L]);
            ++L;
        }
        while (!one.empty() && cnt[one.back()]!=1) {
            inv[one.back()] = false;
            one.pop_back();
        }
        ans[query[i].qid] = one.size() ? one.back() : 0;
    }

    for (int i=0;i<q;i++) {
        printf("%d\n",ans[i]);
    }
    return 0;
}
