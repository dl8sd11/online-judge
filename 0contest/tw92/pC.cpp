#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define X first
#define Y second
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#endif


ll a[100];
ll b[100];
pair<ll,ll> ap[100],bp[100];
bool ac[10][10];
bool bc[10][10];
ll num[100];
int main () {
  REP (i,5) {
    REP (j,5) {
      cin >> a[i*5+j];
      ap[a[i*5+j]] = {i,j};
    }
  }

  REP (i,5) {
    REP (j,5) {
      cin >> b[i*5+j];
      bp[b[i*5+j]] = {i,j};
    }
  }

  REP (i,25) {
    cin >> num[i];
  }

  REP (i,25) {
    ac[ap[num[i]].X][ap[num[i]].Y] = 1;
    bc[bp[num[i]].X][bp[num[i]].Y] = 1;

    ll aw = 0,bw = 0;
    REP (i,5) {
      REP (j,5) {
        if (!ac[i][j]) {
          break;
        }
        if (j==4) {
          aw++;
        }
      }
    }

    REP (j,5) {
      REP (i,5) {
        if (!ac[i][j]) {
          break;
        }
        if (i==4) {
          aw++;
        }
      }
    }

    REP (i,5) {
      if (!ac[i][i]) {
        break;
      }
      if (i==4) {
        aw++;
      }
    }
    REP (i,5) {
      if (!ac[5-i][i]) {
        break;
      }
      if (i==4) {
        aw++;
      }
    }

    REP (i,5) {
      REP (j,5) {
        if (!bc[i][j]) {
          break;
        }
        if (j==4) {
          bw++;
        }
      }
    }


    REP (j,5) {
      REP (i,5) {
        if (!bc[i][j]) {
          break;
        }
        if (i==4) {
          bw++;
        }
      }
    }

    REP (i,5) {
      if (!bc[i][i]) {
        break;
      }
      if (i==4) {
        bw++;
      }
    }
    REP (i,5) {
      if (!bc[5-i][i]) {
        break;
      }
      if (i==4) {
        bw++;
      }
    }
    
    if (aw >= 5) {
      cout <<'A';
    }

    if (bw >= 5) {
      cout <<'B';
    }

    if (aw>=5 || bw>=5) {
      cout << " " << num[i] << endl;
      break;
    }
  }
  return 0;
}