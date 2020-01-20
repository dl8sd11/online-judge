#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;

int n;
string str[MAXN];
ll ans;

const int sz = 2;
typedef array<int,sz> hashtype;

const hashtype mod = {1000000007, 1000000009};
const hashtype cbase = {20020607, 279936};

hashtype operator + (const hashtype &h1, const hashtype &h2) {
    hashtype res;
    for (int i=0;i<sz;i++) {
        res[i] = h1[i] + h2[i];
        if (res[i] >= mod[i]) {
            res[i] -= mod[i];
        }
    }
    return res;
}

hashtype operator - (const hashtype &h1, const hashtype &h2) {
    hashtype res;
    for (int i=0;i<sz;i++) {
        res[i] = h1[i] - h2[i];
        if (res[i] < 0) {
            res[i] += mod[i];
        }
    }
    return res;
}

hashtype operator * (const hashtype &h, const int b) {
    hashtype res;
    for (int i=0;i<sz;i++) {
        res[i] = ll(h[i]) * b % mod[i];
    }
    return res;
}

hashtype operator * (const hashtype &h1, const hashtype &h2) {
    hashtype res;
    for (int i=0;i<sz;i++) {
        res[i] = ll(h1[i]) * h2[i] % mod[i];
    }
    return res;
}


int mpow (int bs, int ep, int md) {
    int ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ll(ret) * bs % md;
        }
        bs = ll(bs) * bs % md;
        ep >>= 1;
    }
    return ret;
}

hashtype inv[MAXN];
void buildInv () {
    inv[0] = {1,1};
    hashtype invb;
    for (int i=0; i<sz; i++) {
        invb[i] = mpow(cbase[i], mod[i]-2, mod[i]);
    }
    for (int i=1;i<MAXN; i++) {
        inv[i] = inv[i-1] * invb;
    }
}

class StringHash {
private:
    int n;
    vector<hashtype> pre;
    bool isRev;
public:
    StringHash (string s, bool rev): n(s.size()), pre(s.size()+1), isRev(rev) {
        if (rev) {
            reverse(s.begin(),s.end());
        }
        hashtype cur = {1, 1};
        for (int i=1;i<=n; i++) {
            int c = s[i-1];
            pre[i] = pre[i-1] + (cur * c);
            cur = cur * cbase;
        }
    }

    hashtype get (int l, int r) {
        if (isRev) {
            swap(l, r);
            l = n-1-l;
            r = n-1-r;
        }

        hashtype res = pre[r+1] - pre[l];
        res = res * inv[l];

        return res;
    }
};

bool isPalindrome (int l, int r, StringHash &sf, StringHash &sr) {
    if (l >= r) {
        return true;
    } else {
        int mid = (l + r) >> 1;
        if ((r-l)&1) {
            return sf.get(l,mid) == sr.get(mid+1,r);
        } else {
            return sf.get(l,mid-1) == sr.get(mid+1,r);
        }
    }

}

vector<StringHash> horg, hrev;

vector<hashtype> hlen[MAXN];

void buildHCnt () {
    REP (i, MAXN) {
        sort(hlen[i].begin(), hlen[i].end());
    }
}

int cntH (int len, hashtype val) {
    return upper_bound(hlen[len].begin(),hlen[len].end(),val) - \
            lower_bound(hlen[len].begin(),hlen[len].end(),val);
}

void solve () {
    REP (i, n) {
        debug(str[i]);
        horg.emplace_back(str[i], false);
        hrev.emplace_back(str[i], true);
        hlen[SZ(str[i])].emplace_back(hrev[i].get(0, SZ(str[i])-1));
    }
    buildHCnt();

    REP (i, n) {
        int csz = SZ(str[i]);
        REP (j, csz) {
            if (isPalindrome(csz-j,csz-1,horg[i],hrev[i])) {
                int dl = cntH(csz-j, horg[i].get(0,csz-1-j));
                debug(i, j, dl);
                ans += dl;
            }

            if (j > 0 && isPalindrome(0,j-1,horg[i],hrev[i])) {
                int dl = cntH(csz-j, horg[i].get(j,csz-1));
                debug(i, j, dl);
                ans += dl;
            }
        }
        if (isPalindrome(0, csz-1,horg[i],hrev[i])) {
            debug(i);
            ans -= 1;
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    buildInv();

    cin >> n;
    REP (i, n) {
        cin >> str[i];
    }

    solve();

    cout << ans << endl;
}

/*
5
aa
a
aaa
a
ab
*/
