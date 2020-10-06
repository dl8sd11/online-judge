#include "simurgh.h"
#include <bits/stdc++.h>

#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;
#define ALL(i) i.begin(),i.end()

static int MAXQ = 300000;

static int n, m, q = 0;
static vector<int> u, v;
static vector<bool> goal;

static void wrong_answer() {
	printf("NO\n");
	exit(0);
}

static bool is_valid(const vector<int>& r) {
	if(int(r.size()) != n - 1)
		return false;

	for(int i = 0; i < n - 1; i++)
		if (r[i] < 0 || r[i] >= m)
			return false;

	return true;
}

static int _count_common_roads_internal(const vector<int>& r) {
	if(!is_valid(r))
		wrong_answer();

	int common = 0;
	for(int i = 0; i < n - 1; i++) {
		bool is_common = goal[r[i]];
		if (is_common)
			common++;
	}

	return common;	
}

int count_common_roads(const vector<int>& r) {
	q++;
	if(q > MAXQ) {
        cout << "GAN" << endl;
		wrong_answer();

    }

	return _count_common_roads_internal(r);
}

struct Djs {
    vector<int> djs;
    Djs(int N) : djs(N) {
        iota(ALL(djs), 0);
    }
    int fnd (int x) {
        return x == djs[x] ? x : djs[x] = fnd(djs[x]);
    }
    bool mrg (int x, int y) {
        x = fnd(x), y = fnd(y);
        if (x == y) return false;
        djs[fnd(x)] = fnd(y);
        return true;
    }
};

int main() {

	assert(2 == scanf("%d %d", &n, &m));

	u.resize(m);
	v.resize(m);

	goal.resize(m, false);
	for(int i = 0; i < m; i++)
		assert(2 == scanf("%d %d", &u[i], &v[i]));


	for(int i = 0; i < n - 1; i++) {
		int id;
		assert(1 == scanf("%d", &id));
		goal[id] = true;
	}
    //n = 5;
    //Djs djs(n);
    //m = 9;
    
    //srand(time(0));
    //set<pair<int,int>> edge;
    //cout << "Real";
    //for (int i=0; i<m; i++) {
        //int U = rand() % n, V = rand() % n;
        //if (U > V) swap(U, V);
        //while (U == V || edge.count(pair<int,int>(U, V))) {
            //U = rand() % n, V = rand() % n;
            //if (U > V) swap(U, V);
        //}
        //if (djs.mrg(U, V)) {
            //goal[i] = true;
            //cout << " " << i;
        //}
        //edge.emplace(U, V);
        //u.emplace_back(U);
        //v.emplace_back(V);
    //}

    //cout  << endl;

	vector<int> res = find_roads(n, u, v);

	if(_count_common_roads_internal(res) != n - 1)
		wrong_answer();

    printf("%d", q);
	printf("YES\n");

	return 0;
}

