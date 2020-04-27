#include <bits/stdc++.h>
using namespace std;

void addRoad(int u, int v);
void buildFarms();
void notifyFJ(int u, int v);

int N;
void setFarmLocation(int ID, int X, int Y) {
    cout << "Farm " << ID << " " << X << " " << Y << endl;
}

void addBox(int X1, int Y1, int X2, int Y2) {
    cout << "Box " << X1 << " " << Y1 << " " << X2 << " " << Y2 << endl;
}

int getN () {
    return N;
}

int main () {
    cin >> N;
    for (int i=0; i<N-1; i++) {
        int u, v;
        cin >> u >> v;
        addRoad(u,v);
    }

    cout << "BUILT" << endl;
    buildFarms();


    int q;
    cin >> q;

    while (q--) {
        int u, v;
        cin >> u >> v;

        cout << "ASK " << u << " " << v <<endl;
        notifyFJ(u, v);
    }
}
