#include <bits/stdc++.h>
using namespace std;
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream& __printRng (ostream& os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg;it!=ed;it++) {
        if (it == bg) os << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream& operator << (ostream& os, const vector<T> &v) {return __printRng(os, ALL(v));}
template<typename T, typename S> ostream& operator << (ostream& os, const pair<T,S> &p) {return os<<"("<<p.X<<","<<p.Y<<")";}
#else
#define debug(...)
#endif

