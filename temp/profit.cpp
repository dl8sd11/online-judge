#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main () {
    int n, m;
    cin >> n >> m;

    int* cnt = new int[n];
    int* idx = new int[n];
    int** edges = new int*[m];
    int** G = new int*[n];
    int* val = new int[n];

    ll sum = 0; 
    for (int i=0; i<n; i++) {
        cin >> val[i];
        sum -= val[i];
        cnt[i] = idx[i] = 0;
    }

    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        cnt[u]++;
        cnt[v]++;
        edges[i] = new int[3];
        edges[i][0] = u;
        edges[i][1] = v;
        edges[i][2] = w;
        sum += w;
    }

    for (int i=0; i<n; i++) {
        G[i] = new int[cnt[i]];        
    }
    for (int i=0; i<m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        G[u][idx[u]++] = i;
        G[v][idx[v]++] = i;
    }


    bool* sel = new bool[n];
    for (int i=0; i<n; i++) sel[i] = true;
    for (int i=n; i>=1; i--) {
        int mx = 0, bst = -1;
        for (int j=0; j<n; j++) { // remove
            int inc = val[j];
            if (sel[j]) {
                for (int k=0; k<cnt[j]; k++) {
                    int eid = G[j][k];
                    int x = edges[eid][0] ^ edges[eid][1] ^ j;
                    if (sel[x]) {
                        inc -= edges[eid][2];
                    }
                }
                if (inc > mx) {
                    bst = j;
                    mx = inc;
                }
            }
        }
        if (bst == -1) {
            break;
        }
        sel[bst] = false;
        sum += mx;
    }

    bool first = true;
    for (int i=0; i<n; i++) {
        if (sel[i]) {
            if (!first) cout << ",";
            first = false;
            cout << i+1;
        }
    }
    cout << ";" << sum << endl;

    delete[] cnt;
    delete[] idx;
    delete[] sel;
    delete[] val;

    for (int i=0; i<n; i++) delete[] G[i];
    for (int i=0; i<m; i++) delete[] edges[i];
    delete[] G;
    delete[] edges;

}
