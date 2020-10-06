#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define first X
#define second Y
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream &__printRng (ostream& os, IT bg, IT ed) {
    for (IT it=bg; it!=ed; it++) {
        if (it == bg) os << "{" << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream &operator << (ostream& os, const vector<T> &vec) {
    return __printRng(os,ALL(vec));
}
#else
#define debug(...)
#endif
