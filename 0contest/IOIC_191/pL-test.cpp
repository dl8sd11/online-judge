#include <bits/stdc++.h>
using namespace std;

int n , m , u[106] , ans;
pair<int,int> x[506];

int main(){
    clock();
    cin >> n >> m;
    for(int i = 0 ;i < m; ++i) cin >> x[i].first >> x[i].second;
    for(int times = 0; times < 5000 * 5000; ++ times){
        random_shuffle(x , x + m);
        memset(u,0,sizeof(u));
        int cnt = 0;
        for(int i = 0 ;i < m; ++i) if(u[x[i].first] == 0 && u[x[i].second] == 0){
            u[x[i].first] = 1;
            u[x[i].second] = 1;
            cnt ++;
        }
        ans = max(ans , cnt);
        if(1.0 * clock() / CLOCKS_PER_SEC > 1.99) break;
    }
    cout << ans << endl;
    return 0;
}