#include "Alicelib.h"
#include <cassert>
#include <cstdio>
#include <bits/stdc++.h>
using namespace std;

void Alice( int N, int M, int A[], int B[] ){
	vector<pair<int,int> > edge;
    for (int i=0;i<M;i++) {
        edge.emplace_back(A[i], B[i]);
    }
    for (int i=0;i<N;i++) {
        edge.emplace_back(N+1,i);
    }
    edge.emplace_back(N,N+2);
    edge.emplace_back(N+1,N+2);

    for (int d=0;d<9;d++) {
        edge.emplace_back(N+d+2, N+d+3);
        for (int i=0;i<N;i++) {
            if (i & (1<<d)) {
                edge.emplace_back(i, N+d+3);
            }
        }
    }

    InitG(N+12, edge.size());
    int idx = 0;
    for (auto p : edge) {
        MakeG(idx++, p.first, p.second);
    }
}

