#include <bits/stdc++.h>
using namespace std;

map<int, int> app;
int cnt[100005];

int maxEqualFreq(vector<int>& nums) {
    int ans = 0, it = 0;
    for (auto v : nums) {
        it++;

        app[cnt[v]]--;
        if (app[cnt[v]] <= 0) {
            app.erase(cnt[v]);
        }
        cnt[v]++;
        app[cnt[v]]++;
        
        if (app.size() == 1) {
            if (app.begin()->first == 1 || app.begin()->second == 1) {
                ans = max(ans, it);
            }
        } else {
            auto lst = prev(app.end());
            if (lst->first * lst->second == it - 1) {
                ans = max(ans, it);
            } else if (lst->first == 1 && lst->second == it) {
                ans = max(ans, it);
            } else {
                auto llst = prev(lst);
                if (llst->first == lst->first - 1 && llst->first*(llst->second+1) == it-1) {
                    ans = max(ans, it);
                }
            }
        }
    }
    return ans;
}
/********** Good Luck :) **********/
int main () {


    // cout << maxEqualFreq({2,2,1,1,5,3,3,5}) << endl;
    // cout << maxEqualFreq({1,1,1,2,2,2,3,3,3,4,4,4,5}) << endl;
    // cout << maxEqualFreq({1,1,1,2,2,2}) << endl;
    cout << maxEqualFreq({10,2,8,9,3,8,1,5,2,3,7,6}) << endl;
    return 0;
}
