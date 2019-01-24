#include <bits/stdc++.h>
using namespace std;

vector<char> st;
int main () {
    int cnt = 0;

    string s;
    cin >> s;

    for (auto c : s) {
        if (st.empty()) {
            st.emplace_back(c);
        } else if (st.back() == c) {
            cnt++;
            st.pop_back();
        } else {
            st.emplace_back(c);
        }
    }

    cout << (cnt&1?"Yes":"No") << endl;
}