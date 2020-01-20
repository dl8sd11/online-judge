#include <cstdio>
#include <vector>
#include "library.h"
#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())

int n;

int vecQuery(const vector<int> &vec) {
	vector<int> M(n);
    for (auto el : vec) {
        M[el-1] = true;
    }
    return Query(M);
}

vector<int> res;

void init () {
    vector<int> M(n, 1);

    vector<int> ht;
    for (int i=0; i<n; i++) {
        M[i] = false;

        if (Query(M) == 1) {
            ht.emplace_back(i+1);
        }

        M[i] = true;
    }

    assert(ht.size() == 2);
    res[0] = ht[0];
    res[n-1] = ht[1];
}

void build () {
    set<int> left;
    REP1 (i, n) {
        left.insert(i);
    }
    left.erase(res[0]);
    left.erase(res[n-1]);

    for (int i=1; i<n-1; i++) {
        vector<int> cur;
        for (auto v : left) {
            cur.emplace_back(v);
        }

        while (SZ(cur) > 1) {
            vector<int> hf;
            vector<int> hs;
            REP (j, SZ(cur)) {
                if (j < SZ(cur)/2) {
                    hf.emplace_back(cur[j]);
                } else {
                    hs.emplace_back(cur[j]);
                }
            }

            int q1 = vecQuery(hf);
            hf.emplace_back(res[i-1]);
            if (q1 == vecQuery(hf)) {
                hf.pop_back();
                cur = hf;
            } else {
                cur = hs;
            }
        }

        res[i] = cur.front();
        left.erase(cur.front());
    }
}

void Solve(int N)
{
    n = N;
    res.resize(N);

    if (n == 1) {
        res[0] = 1;
    } else {
        init();
        build();
    }

	Answer(res);
}
