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
const ll MOD = 1000000007;

typedef vector<short> BigInteger;

BigInteger buildBigInteger (string str) {
    BigInteger result;
    result.reserve(str.size());

    for (auto it=str.rbegin(); it!=str.rend(); it++) {
        result.emplace_back((*it) - '0');
    }

    return result;
}

BigInteger buildBigInteger (short a) {
    if (a == 0) {
        return {0};
    }

    BigInteger result;
    while (a) {
        result.emplace_back(a%10);
        a /= 10;
    }

    return result;
}

void trimLeadingZeros (BigInteger &a) {
    while (a.size() > 1&& a.back() == 0) {
        a.pop_back();
    }
}

BigInteger operator+ (const BigInteger &a, const BigInteger &b) {
    BigInteger result;
    auto maxLen = max(a.size(), b.size());

    short carry = 0;
    for (size_t i=0; i<=maxLen; i++) {
        short current = carry;
        if (i < a.size()) {
            current += a[i];
        }
        if (i < b.size()) {
            current += b[i];
        }

        result.emplace_back(current % 10);
        carry = current / 10;
    }

    trimLeadingZeros(result);
    return result;
}

BigInteger operator- (const BigInteger &a, const BigInteger &b) {
    BigInteger result;
    auto maxLen = max(a.size(), b.size());

    short carry = 0;
    for (size_t i=0; i<=maxLen; i++) {
        short current = carry;
        if (i < a.size()) {
            current += a[i];
        }
        if (i < b.size()) {
            current -= b[i];
        }

        if (current < 0) {
            carry = -1;
            current += 10;
        } else {
            carry = 0;
        }

        result.emplace_back(current);
    }

    trimLeadingZeros(result);
    return result;
}

BigInteger operator* (const BigInteger &a, const BigInteger &b) {
    BigInteger result(a.size()+b.size());

    for (size_t i=0; i<a.size(); i++) {
        for (size_t j=0; j<b.size(); j++) {
            result[i+j] += a[i] * b[j];
        }
    }

    short carry = 0;
    for (short &d : result) {
        d += carry;
        carry = d / 10;
        d = d % 10;
    }

    trimLeadingZeros(result);
    return result;
}

BigInteger operator* (const BigInteger &a, short b) {
    return a * buildBigInteger(b);
}

BigInteger operator+ (const BigInteger &a, short b) {
    return a + buildBigInteger(b);
}

bool operator> (BigInteger a, BigInteger b) {
    trimLeadingZeros(a);
    trimLeadingZeros(b);
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    for (size_t i=a.size()-1; i+1 > 0; i--) {
        if (a[i] != b[i]) {
            return a[i] > b[i];
        }
    }
    return false;
}

BigInteger operator/ (const BigInteger &a, const BigInteger &b) {
    BigInteger result(a.size()), remain = {0};
    for (size_t i=a.size()-1; i+1 > 0; i--) {
        remain = (remain * 10) + a[i];

        short k;
        for (k=1; k<=10; k++) {
            BigInteger buf = b * k;
            if (buf > remain) {
                break;
            }
        }

        k--;
        result[i] = k;
        remain = remain - (b * k);
    }

    trimLeadingZeros(result);
    return result;
}




void Print (BigInteger a) {
    trimLeadingZeros(a);

    for (auto it=a.rbegin(); it!=a.rend(); it++) {
        cout << *it;
    }
    cout << endl;
}

/*********************GoodLuck***********************/
int main () {
    IOS();
    string astr, bstr;
    char opr;
    cin >> astr >> opr >> bstr;

    BigInteger a = buildBigInteger(astr), b = buildBigInteger(bstr);

    if (opr == '*') {
        Print(a * b);
    } else {
        Print(a / b);
    }
}
