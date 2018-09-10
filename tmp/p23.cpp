  #include <bits/stdc++.h>

  using namespace std;
  // -----------------------------------------------------------------------------------------------------------------------------------

  int t=0,now;
  stack<int> s1,s2;

  void solve(int N,int order[]);
  void push_train();
  void move_station_1_to_2();
  void move_station_2_to_1();
  void pop_train();

  void solve(int N,int order[]){
    t=0;
    while(s1.size())s1.pop();
    while(s2.size())s2.pop();

  	for(int i=0;i<N;i++){
  		push_train();
  		move_station_1_to_2();
  		s2.push(i+1);
  	}
  	now=1;
  	while(t<N){
  		if(order[t]>=now){
  			while(s2.top()!=order[t]){
  				s1.push(s2.top());
  				s2.pop();
  				move_station_2_to_1();
  			}
  			s2.pop();
  			pop_train();
  			now=s2.top();
  			t++;
  		}else {
  			while(s2.top()!=order[t]){
  				s2.push(s1.top());
  				s1.pop();
  				move_station_1_to_2();
  			}
  			s2.pop();
  			pop_train();
  			now=s2.top();
  			t++;
  		}
  	}
  }
