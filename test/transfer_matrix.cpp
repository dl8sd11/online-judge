#include <bits/stdc++.h>

using namespace std;

#ifdef Sia
#define deb(...)    do{fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_out(__VA_ARGS__);}while(0);
template<typename T>                 void _out(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S>  void _out(T &&x, S &&...y){cerr<<x<<", ";_out(y...);}
template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p){return os<<"("<<p.first<<", "<<p.second<<")";}
template<typename It>            ostream& _out_it(ostream &os, It ita, It itb) {
	os << "{"; for(It it = ita; it != itb; ++it) os << (it == ita ? "" : ", ") << *it; os << "}";
	return os; }
template<typename T, typename S> ostream& operator << (ostream &os, map<T, S> &m){return _out_it(os, m.begin(), m.end());}
template<typename T>             ostream& operator << (ostream &os, set<T>    &s){return _out_it(os, s.begin(), s.end());}
template<typename T>             ostream& operator << (ostream &os, vector<T> &v){return _out_it(os, v.begin(), v.end());}
template<typename T>                 void debit(T a, T b){_out_it(cerr, a, b); cerr << endl;}
#define INITIO()    cout<<setprecision(numeric_limits<double>::max_digits10+1);
#else
#define deb(...)
#define debit(...)
#define endl        '\n'
#define INITIO()    ios_base::sync_with_stdio(false);cin.tie(NULL);cout<<setprecision(numeric_limits<double>::max_digits10+1);
#endif
#define MEM(i,j) 	memset(i,j,sizeof i);
#define X           first
#define Y           second
#define pb          push_back
#define mp          make_pair
#define ALL(a)      a.begin(),a.end()
typedef				long long ll;
typedef				unsigned long long ull;
typedef				pair<ll,ll> pii;
const double Eps  = 1e-8;
const ll Inf      = 1e18+7;
const int Mod     = 1e9+7;
// -----------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 200;

int main(){
	INITIO()
  cout << RAND_MAX << endl;
	srand(time(NULL));
	ll n=3;//rand()%100+1;
	vector<double> q[MAXN];
	
	for(int i=0;i<n;i++){
		ll tmp=1e6;
		//cout<<tmp<<endl;
		for(int j=1;j<n;j++){
			ll ttmp=rand()%tmp;
			//cout<<'t'<<ttmp<<endl;
			q[i].pb(double(ttmp/1e6));
			tmp-=ttmp;
			//cout<<tmp<<endl;
		}
		q[i].pb(double(tmp/1e6));
		//cout<<tmp<<endl;
	}
	
	cout<<n<<endl;
	for(int j=0;j<n;j++){
		for(int i=0;i<n;i++){
			cout<<q[i][j]<<' ';
		}
		cout<<endl;
	}
}