#include <iostream>
using namespace std;

void hanoi (int from, int past, int dest, int n) {
    char pillar[] = {'A','B','C'};
    if (n != 0) {
        hanoi(from,dest,past,n-1);
        cout << "Move ring " << n << " from " << pillar[from] << " to " << pillar[dest] << endl;
        hanoi(past,from,dest,n-1);
    }
}

int main () {
    int n;
    cin >> n;
    hanoi(0,1,2,n);
}