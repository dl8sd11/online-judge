#include <bits/stdc++.h>
#include "books.h"

#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

int main() {
	int n, s;
    srand(time(0));
	//assert(2 == scanf("%d %d", &n, &s));

	//for(int i = 0; i < n; i++)
		//assert(1 == scanf("%d", &p[(unsigned) i]));
    n = 4, s = 1;
	vector<int> p((unsigned) n);
    iota(p.begin(), p.end(), 0);

    while (true) {

        random_shuffle(p.begin(), p.end());

        long long res = minimum_walk(p, s);
        printf("%lld\n", res);
    }

	return 0;
}
