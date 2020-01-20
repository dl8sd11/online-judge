#include <iostream>
#include <string>
using namespace std;

int n, h ,t;

void go() {
    cin >> n;
    h = n/100-(n/1000)*10;
    t = n/1000-(n/10000)*10;
    if ( h%2==0 && t%3==2||0||0){
        cout << "Y890916" <<endl;
    }
    else if (h%3==0 && t%4!=0 && (h+t)%5==0){
        cout << "X890916" << endl;
    }
    else
        cout << "0" <<endl;
}

int main(){
    int T; cin >> T;
    while (T--) {
        go();
    }
}