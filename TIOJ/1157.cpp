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

const int MAXN = 51;
const ll MOD = 1000000007;

struct Fract {
    ll a, b;
    Fract () {
        a = 0;
        b = 1;
    }
};

ostream& operator << (ostream &os, const Fract &f) {
    if (f.b == 1) {
        os << f.a;
    } else {
        os << f.a << "/" << f.b;
    }
    return os;
};

istream& operator >> (istream &is, Fract &f) {
    f.b = 1;
    is >> f.a;
    return is;
}

void nrm (Fract &f) {
    ll gcd = __gcd(f.a, f.b);
    f.a /= gcd;
    f.b /= gcd;
    if (f.b < 0) {
        f.a *= -1;
        f.b *= -1;
    }
}

Fract operator * (const Fract &f1, const Fract &f2) {
    Fract ret;
    ret.a = f1.a * f2.a;
    ret.b = f1.b * f2.b;
    nrm(ret);
    return ret;
}


Fract neg (const Fract &f1) {
    Fract ret;
    ret.a = -f1.a;
    ret.b = f1.b;
    nrm(ret);
    return ret;
}

Fract operator + (const Fract &f1, const Fract &f2) {
    Fract ret;
    ret.a = f1.a*f2.b+f2.a*f1.b;
    ret.b = f1.b*f2.b;
    nrm(ret);
    return ret;
}

Fract operator - (const Fract &f1, const Fract &f2) {
    Fract ret = f1 + neg(f2);
    nrm(ret);
    return ret;
}

Fract rev (const Fract &f1) {
    Fract ret;
    ret.a = f1.b;
    ret.b = f1.a;
    nrm(ret);
    return ret;
}

Fract operator / (const Fract &f1, const Fract &f2) {
    return f1 * rev(f2);
}

void operator *= (Fract &f1, const Fract &f2) {
    f1 = f1 * f2;
}

void operator /= (Fract &f1, const Fract &f2) {
    f1 = f1 / f2;
}

void operator += (Fract &f1, const Fract &f2) {
    f1 = f1 + f2;
}

void operator -= (Fract &f1, const Fract &f2) {
    f1 = f1 - f2;
}



int n;
Fract coff[MAXN][MAXN], res[MAXN];

void Triangularize () {
    REP (i, n) {
        if (coff[i][i].a == 0) {
            int fnd = -1;
            for (int j=i+1; j<n; j++) {
                if (coff[j][i].a != 0) {
                    fnd = j;
                    break;
                }
            }

            if (fnd == -1) {
                continue;
            } else {
                debug(i, fnd);
                REP (j, n) {
                    swap(coff[i][j], coff[fnd][j]);
                }
                swap(res[i], res[fnd]);
            }
        }

        Fract hd = coff[i][i];
        assert(hd.a != 0);

        REP (j, n) {
            coff[i][j] /= hd;
        }
        res[i] /= hd;

        for (int j=i+1; j<n; j++) {
            Fract c = neg(coff[j][i]);
            REP (k, n) {
                coff[j][k] += coff[i][k] * c;
            }
            res[j] += res[i] * c;
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    REP (i, n) {
        REP (j, n) {
            cin >> coff[i][j];
        }
        cin >> res[i];
    }


    Triangularize();

    bool noAns = false, mulAns = false;

    for (int i=n-1; i>=0; i--) {
        for (int j=i+1; j<n; j++) {
            res[i] -= coff[i][j] * res[j];
            coff[i][j] -= coff[i][j];
        }
        if (coff[i][i].a == 0) {
            if (res[i].a == 0) {
                mulAns = true;
            } else {
                noAns = true;
            }
        }
    }

    #ifdef tmd
    REP (i, n) {
        REP (j, n) {
            cout << coff[i][j] << " ";
        }
        cout << res[i] << endl;
    }
    #endif // tmd

    if (noAns) {
        cout << 0 << endl;
    } else if (mulAns) {
        cout << "N" << endl;
    } else {
        cout << 1 << endl;
        REP (i, n) {
            nrm(res[i]);
            assert(coff[i][i].a = 1);
            cout << "x" << i+1 << " = " << res[i] << endl;
        }
    }

}
