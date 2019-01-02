#include <bits/stdc++.h>
using namespace std;

int cnt[1505];
void initialize(int n){
    for(int i=0;i<n;i++) cnt[i]=0;
}
int hasEdge(int a, int b){
    if(++cnt[max(a,b)]==max(a,b))return 880301;
    else return 0;
}
