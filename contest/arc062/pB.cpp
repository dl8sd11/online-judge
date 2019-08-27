#include <iostream> 
using namespace std;
int n, ans;
string s;

int main() {
    cin >> s;
    n = s.size()-1;
    for (int i=0;i<=n;i++) ans += (i > n/2) - (s[i] == 'p');    
    cout << ans << endl;
    return 0;
}
