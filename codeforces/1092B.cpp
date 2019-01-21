#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
long long int n,xsum,ysum;;
pair<int,int> pos[2000],del[2000];

int main () {
    cin >> n;
    for (int i=0;i<n;i++) {
        cin >> pos[i].X >> pos[i].Y;
        xsum += pos[i].X;
        ysum += pos[i].Y;
    }
    for (int i=0;i<n;i++) {
        cin >> del[i].X >> del[i].Y;
        xsum += del[i].X;
        ysum += del[i].Y;
    }

    xsum /= n;
    ysum /= n;

    cout << xsum << " " << ysum << endl;
}