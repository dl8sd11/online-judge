
#include<bits/stdc++.h>
using namespace std;

int main(){
	static int arr[200003]; int N , K;
	cin >> N >> K; for(int i = 1 ; i <= N ; ++i) cin >> arr[i];
	set < int > num; int ans = 1;
	for(int i = 1 ; i <= K ; ++i) num.insert(arr[i]);
	for(int i = K + 1 ; i <= N ; ++i){
		ans += *num.begin() != arr[i - K] || *--num.end() > arr[i];
		num.erase(arr[i - K]); num.insert(arr[i]);
	}
	bool flg = 0; int pre = -1 , cnt = 0;

    cout << ans << endl;
	for(int i = 1 ; i <= N ; ++i){
		if(pre < arr[i]) ++cnt;
		else cnt = 1;
		pre = arr[i];
        cout << cnt << endl;
		if(cnt == K){flg = 1; --ans;}
	}
	cout << ans + flg; return 0;
}
