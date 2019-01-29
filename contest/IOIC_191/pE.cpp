// =＾● ⋏ ●＾=
#include <bits/stdc++.h>
using namespace std;

int HP;

struct towers {
    int cost;
    string tower;
    towers(int c = 1000000000, string t = ""): cost(c), tower(t) {}
    void update(const string &s) {
        int t = 0;
        for (int i = 0; i < 6; ++i) {
            if (s[i] == 'G') t += 3;
            else if (s[i] == 'R') t += 10;
            else if (s[i] == 'S') t += 5;
        }
        if (t < cost) cost = t, tower = s;
        else if (t == cost && s < tower) tower = s;
    }
} ans[10];

struct monster {
    int hp, stay;
    monster(int a = 0, int b = 0): hp(a), stay(b) {}
};

int delay[10];
deque<monster> grid[10];
void hit(string s) {
    memset(delay, 0, sizeof(delay));
    printf("%s",s);
    for (int i = 1; i <= 6; ++i) delay[i] = 1;
    for (int i = 1; i <= 6; ++i) if (s[i - 1] == 'S') for (int z = 0; z < 5 && i + z <= 6; ++z) ++delay[i + z];
    for (int i = 1; i <= 6; ++i) grid[i].clear();
    int monster_on_grid = 0, nowt = 0;
    while (monster_on_grid > 0 || nowt == 0) {
        ++nowt;
        for (int i = 6; i >= 1; --i) {
            while (grid[i].size()) {
                if (grid[i].front().stay == delay[i] - 1) {
                    grid[i + 1].emplace_back(grid[i].front().hp, 0);
                    grid[i].pop_front();
                    if (i == 6) --monster_on_grid;
                }
                else break;
            }
            for (auto &m : grid[i]) ++m.stay;
        }
        if (nowt <= 6) {
            grid[1].emplace_back(HP, 0);
            ++monster_on_grid;
        }
        for (int i = 1; i <= 6; ++i) {
            if (s[i - 1] == 'G') {
                if (grid[i].size()) {
                    --grid[i].front().hp;
                    if (grid[i].front().hp <= 0) {
                        grid[i].pop_front();
                        --monster_on_grid;
                    }
                }
            }
            else if (s[i - 1] == 'R' && nowt % 3 == 0) {
                for (int j = 0; j < int(grid[i].size()); ++j) grid[i][j].hp -= 4;
                deque<monster> tmp;
                for (int j = 0; j < int(grid[i].size()); ++j) {
                    if (grid[i][j].hp <= 0) --monster_on_grid;
                    else tmp.push_back(grid[i][j]);
                }
                grid[i] = tmp;
            }
        }
    }
    int killed = 6 - grid[7].size();
    ans[killed].update(s);
}

void generate(string s) {
    if (s.size() == 6u) {
        hit(s);
        return;
    }
    generate(s + '.');
    generate(s + 'G');
    generate(s + 'S');
    generate(s + 'R');
    return;
}

void meow() {
    for (int i = 0; i <= 6; ++i) ans[i] = towers();
    generate("");
    stack<int> print;
    print.push(6);
    int lac = ans[6].cost;
    for (int i = 5; i >= 1; --i) if (ans[i].cost < lac) print.push(i), lac = ans[i].cost;
    while (print.size()) {
        if (ans[print.top()].cost > 1000) break;
        cout << "$" << ans[print.top()].cost << " -> kill " << print.top() << " with " << ans[print.top()].tower << endl;
        print.pop();
    }
}

int main() {
    cin >> HP;
    meow();
}