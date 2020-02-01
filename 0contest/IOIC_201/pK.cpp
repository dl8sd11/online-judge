#include <bits/stdc++.h>
using namespace std;
#define maxn 1001
#define F first
#define S second

vector<int> v[maxn];
vector<pair<int, int>> seg[maxn];

int dis[maxn], trs[maxn], u[maxn], trspo = 0;

int calcDis(int now) { // 計算每個點的出發可以走到的最長路距離
    if (dis[now] != 0) return dis[now];
    for (auto to : v[now])
        dis[now] = max(dis[now], calcDis(to) + 1);
    return dis[now];
}

inline int cmp(int v1, int v2) { // 排序
    return dis[v1] > dis[v2];
}

void dfs(int now) { // 計算拓樸排序
    if (u[now]) return;
    u[now] = 1;
    sort(v[now].begin(), v[now].end(), cmp);
    for (auto to : v[now]) dfs(to);
    trs[now] = ++trspo;
}

void calc(int now) { // 計算每個點的答案
    if (u[now]) return ;
    u[now] = 1;
    seg[now].emplace_back(trs[now], trs[now]); // 加入這個點的權重
    for (auto to : v[now]) calc(to);           // 計算子樹的答案
    for (auto to : v[now]) {                   // 子樹可以走到的點自己也可以走到，
        vector<pair<int, int>> tmp;            // 將子樹的答案加進現在的點
        int pos = 0;
        for (auto val : seg[to]) {
            while (pos < seg[now].size() && seg[now][pos].F <= val.S + 1) {
                tmp.emplace_back(seg[now][pos ++]);
            }
            while (tmp.size() && tmp.back().S + 1 >= val.F) {
                if (tmp.back().F < val.F) val.F = tmp.back().F;
                if (tmp.back().S > val.S) val.S = tmp.back().S;
                tmp.pop_back();
            }
            tmp.emplace_back(val);
        }
        while (pos < seg[now].size()) tmp.emplace_back(seg[now][pos ++]);
        swap(seg[now], tmp);
    }
}

int n, m, in[maxn];
int main() {
    cin.tie(0), cout.sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 1; i <= m; ++ i) {
        int v1, v2;
        cin >> v1 >> v2;
        v[v1].emplace_back(v2), in[v2] ++;
    }

    vector<pair<int, int>> sol;
    for (int i = 1; i <= n; ++ i) 
        if (in[i] == 0) sol.emplace_back(calcDis(i), i);

    sort(sol.begin(), sol.end(), greater<pair<int, int>>()); // 步驟 2

    for (auto to : sol) dfs(to.S);                           // 步驟 3

    memset(u, 0, sizeof u);

    for (auto to : sol) calc(to.S);                          // 步驟 4

    int sum_size = 0;
    for (int i = 1; i <= n; ++ i)
        sum_size += seg[i].size();


    cout << sum_size << endl;
    // while (sum_size >= 1600);
    return 0;
}

/*
12 12
1 2
3 4
4 5
6 7
7 8
8 9
10 11
10 12
11 2
11 7
12 2
12 7
*/