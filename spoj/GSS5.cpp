#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
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
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 10004;


int t, n, m, a[MAXN], dL[MAXN * 4], dR[MAXN * 4], dAns[MAXN * 4], dSum[MAXN * 4];

void build(int o, int l, int r) {
    if (l == r-1) {
        dAns[o] = dSum[o] = dL[o] = dR[o] = a[l];
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        dL[o] = max(dL[o<<1], dSum[o<<1] + dL[o<<1|1]);
        dR[o] = max(dR[o<<1|1], dSum[o<<1|1] + dR[o<<1]);
        dAns[o] = max({dAns[o<<1], dAns[o<<1|1], dR[o<<1] + dL[o<<1|1]});
        dSum[o] = dSum[o<<1] + dSum[o<<1|1];
    }
}

array<int,4> ept = {910607, 2002, 100006, 100007};
array<int,4> rept = {-iNF, -iNF, -iNF, 0};

array<int, 4> query(int o, int nL, int nR, int qL, int qR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return ept;
    } else if (nL >= qL && nR <= qR) {
        return {dL[o], dR[o], dAns[o], dSum[o]};
    } else {
        int mid = (nL + nR) >> 1;
        array<int,4> lRet = query(o<<1, nL, mid, qL, qR);
        array<int,4> rRet = query(o<<1|1, mid, nR, qL, qR);
        if (lRet == ept) {
            return rRet;
        } else if (rRet == ept) {
            return lRet;
        } else {
            array<int,4> ret;
            ret[0] = max(lRet[0], lRet[3] + rRet[0]);
            ret[1] = max(rRet[1], rRet[3] + lRet[1]);
            ret[2] = max({lRet[2], rRet[2], lRet[1] + rRet[0]});
            ret[3] = lRet[3] + rRet[3];
            return ret;
        }
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> n;
        REP (i, n) {
            cin >> a[i];
        }
        build(1, 0, n);
        pary(a, a+n);
        pary(dL, dL+2*n);
        pary(dR, dR+2*n);
        pary(dSum, dSum+2*n);
        pary(dAns, dAns+2*n);

        cin >> m;
        while (m--) {
            int lL, lR, rL, rR;
            cin >> lL >> lR >> rL >> rR;
            lL--, lR--, rL--, rR--;
            if (lR < rL) {
                array<int, 4> sL = query(1, 0, n, lL, lR+1), sM = query(1, 0, n, lR+1, rL), sR = query(1, 0, n, rL, rR+1);
                if (sM == ept) {
                    sM = rept;
                }
                debug(sL[1], sM[3], sR[0]);
                cout << sL[1] + sM[3] + sR[0] << endl;
            } else {
                array<int,4> sL = query(1, 0, n, lL, rL), sM = query(1, 0, n, rL, lR+1), sR = query(1, 0, n, lR+1, rR+1);
                if (sL == ept) {
                    sL = rept;
                }
                if (sM == ept) {
                    sM = rept;
                }
                if (sR == ept) {
                    sR = rept;
                }

                int ans = sM[2];
                ans = max(ans, sL[1] + sM[3] + sR[0]);
                ans = max(ans, sL[1] + sM[0]);
                ans = max(ans, sM[1] + sR[0]);
                cout << ans << endl;
            }
        }

    }
    return 0;
}
