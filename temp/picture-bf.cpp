#include <bits/stdc++.h>
using namespace std;
using pvec = vector<pair<int,int> >;
using ll = long long;

#ifdef tmd
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) static_cast<int>(i.size())
#define FOR(i, j, k, in) for (int i=j; i < (k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j; i >= (k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(), _a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
template<typename T, typename S>
istream &operator >> (istream &is, pair<T, S> &p) {
    return is >> p.X >> p.Y;
}
#define TIME(i) Timer i(#i)
#define debug(...) do {\
    fprintf(stderr, "%s - %d (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<" ,"; _do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << "," << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":",")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _a, size_t _b> ostream &operator << (ostream &_s, const array<_a,_b> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s, const map<_a,_b> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define debug(...)
#endif

struct Trans {
    int i, l, r;
};
ostream &operator << (ostream &_s, const Trans& tr) {
    return _s << "{"  << tr.i << "," << tr.l << "," << tr.r << "}";
}

pvec orderLow (pvec vec) {
    pvec res;
    sort(vec.begin(), vec.end());
    for (auto p : vec) {
        if (res.empty() || p.second < res.back().second) {
            res.push_back(p);
        }
    }
    return res;
}

pvec orderHigh (pvec vec) {
    pvec res;
    sort(vec.begin(), vec.end());
    for (auto p : vec) {
        while (res.size() && res.back().second <= p.second) {
            res.pop_back();
        }
        res.push_back(p);
    }
    return res;
}
ll solve (pvec plo, pvec phi) {
    ll mans = 0;
    auto f = [&](int i, int j) {
        assert(i < plo.size());
        assert(j < phi.size());
        return (plo[i].first >= phi[j].first || plo[i].second >= phi[j].second) ?
            0 : (ll(plo[i].first - phi[j].first) * (plo[i].second - phi[j].second));
    };
    int m = int(plo.size()), n = int(phi.size());
    sort(plo.begin(), plo.end());
    sort(phi.begin(), phi.end());
    plo = orderLow(plo);
    phi = orderHigh(phi);
    m = int(plo.size()), n = int(phi.size());

    deque<Trans> deq;


    int R = 0;
    for (int i=0; i<m; i++) {
        while (R < n && phi[R].second > plo[i].second) {
            R++;
        }
        while (!deq.empty() && \
             f(deq.back().i, deq.back().l) < f(i, deq.back().l)) {
            deq.pop_back();
        }
        if (!deq.empty()) {
            int l = deq.back().l, r = deq.back().r;
            while (l < r - 1) {
                int mid = (l + r) >> 1;
                if (f(deq.back().i, mid) < f(i, mid)) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            deq.back().r = r;
            if (r != R) deq.push_back({i, r, R});
        } else {
            deq.push_back({i, 0, R});
        }
    }

    vector<ll> mx;
    for (int i=0; i<n; i++) {
        while (deq.size() && deq.front().r <= i) {
            deq.pop_front();
        }
        if (deq.size()) {
            mx.push_back(f(deq.front().i, i));
        }
    }

    ll ans = mx.empty() ? 0LL : *max_element(mx.begin(), mx.end());

    return ans;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, n;
    cin >> m >> n;
    vector<pair<int,int> > plo(m), phi(n);

    for (int i=0; i<m; i++) {
        cin >> plo[i].first >> plo[i].second;
    }
    for (int i=0; i<n; i++) {
        cin >> phi[i].first >> phi[i].second;
    }

    ll ans = 0;
    for (auto p1 : plo) {
        for (auto p2 : phi) {
            if (p2.second > p1.second && p2.first > p1.first) {
                ans = max(ans, ll(p2.second - p1.second)*(p2.first - p1.first));
            }

        }
    }

    cout << ans << endl;

}
