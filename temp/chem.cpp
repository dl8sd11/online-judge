#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double, double> pdd;
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
#ifdef tmd
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
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

#define stack vector
#define top back
#define push push_back
#define pop pop_back

int chartoint(char);

int chartoint(char x)
{
	return x-'0';
}

int main()
{
	string Chemform;
	cin>>Chemform;
	map<string,int> Chemcount;
	map<string,int>::iterator it;
	stack< map<string, int> > gua;
	for(int i=0;i<Chemform.size();i++)
	{
		string element;
		element="";
		if(Chemform[i]=='(')
		{
			gua.push(Chemcount);
			Chemcount=map<string, int>();
		}
		else if(Chemform[i]==')')
		{
            if (Chemcount.size()) gua.push(Chemcount);
			Chemcount=map<string, int>();
			map<string,int> tem1=gua.top();
			/*for(auto iit = tem1.begin(); iit != tem1.end(); iit++)
			{
				cout<<iit->first<<iit->second;
			}
			cout<<endl;*/
			gua.pop();
			for(auto iit = tem1.begin(); iit != tem1.end(); iit++)
			{
				iit->second=iit->second*chartoint(Chemform[i+1]);
			}
			map<string,int> tem2=gua.top();
			for(auto iit = tem1.begin(); iit != tem1.end(); iit++)
			{
				it=tem2.find(iit->first);
				if(it!=tem2.end()) tem2[iit->first] += iit->second;
				else tem2.insert(pair<string,int>(iit->first,iit->second));
			}
			gua.pop();
			gua.push(tem2);
			/*map<string, int> tem3=gua.top();
			for(auto iit = tem3.begin(); iit != tem3.end(); iit++)
			{
				cout<<iit->first<<iit->second;
			}
			cout<<endl;*/
		}
		if(i==Chemform.size()-1&&Chemform[i]>='A'&&Chemform[i]<='Z') 
		{
			element=element+Chemform[i];
			it=Chemcount.find(element);
			if(it!=Chemcount.end()) Chemcount[element]++;
			else Chemcount.insert(pair<string,int>(element,1));
		}
		if(i<Chemform.size()-1&&Chemform[i]>='A'&&Chemform[i]<='Z')
		{
			if(Chemform[i+1]>='a'&&Chemform[i+1]<='z')
			{
				element=element+Chemform[i]+Chemform[i+1];
				if(i+1==Chemform.size()-1||(Chemform[i+2]>='A'&&Chemform[i+2]<='Z')||Chemform[i+2]=='(')
				{
					it=Chemcount.find(element);
					if(it!=Chemcount.end()) Chemcount[element]++;
					else Chemcount.insert(pair<string,int>(element,1));
				}
				else
				{
					it=Chemcount.find(element);
					int Num;
					Num=Chemform[i+2]-'0';
					if(it!=Chemcount.end()) Chemcount[element]+=Num;
					else Chemcount.insert(pair<string,int>(element,Num));
				}
			}
			else
			{
				element+=Chemform[i];
				if(Chemform[i+1]>='0'&&Chemform[i+1]<='9')
				{
					it=Chemcount.find(element);
					int Num=Chemform[i+1]-'0';
					if(it!=Chemcount.end()) Chemcount[element]+=Num;
					else Chemcount.insert(pair<string,int>(element,Num));
				}
				else
				{
					it=Chemcount.find(element);
					if(it!=Chemcount.end()) Chemcount[element]++;
					else Chemcount.insert(pair<string,int>(element,1));
				}
				
			}
		}
        debug(Chemcount, gua);
	}
	if(Chemcount.empty()) Chemcount=gua.top();
	for (auto iit = Chemcount.begin(); iit != Chemcount.end(); iit++) {
  		if(iit->second==1) cout<<iit->first;
        else cout<<iit->first<<iit->second;
    }
	
 } 
