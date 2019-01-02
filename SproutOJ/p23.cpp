#include <bits/stdc++.h>
using namespace std;
stack<int> q[2];
stack<int> m[4];
int total;

void push_train(){
  cout<<"Push Train: "<<m[0].top()<<endl;
  m[1].push(m[0].top());
  m[0].pop();
}
void move_station_1_to_2(){
  cout<<"Move 1 to 2: "<<m[1].top()<<endl;
  m[2].push(m[1].top());
  m[1].pop();
}void move_station_2_to_1(){
  cout<<"Move 2 to 1: "<<m[2].top()<<endl;
  m[1].push(m[2].top());
  m[2].pop();
}
void pop_train(){
  cout<<"Pop Train: "<<m[2].top()<<endl;
  m[3].push(m[2].top());
  m[2].pop();
}


void getfroml(int tg){
  for (int i = 0; i < total; i++) {
    if (q[1].top() == tg) {
      pop_train();
      q[1].pop();
    } else {
      move_station_2_to_1();
      q[0].push(q[1].top());
      q[1].pop();
    }
  }
  total--;
}
void getfromr(int tg){
  for (int i = 0; i < total; i++) {
    move_station_1_to_2();
    if (q[0].top() == tg) {
      pop_train();
      q[0].pop();
    } else {
      q[1].push(q[0].top());
      q[0].pop();
    }
  }
  total--;
}


void solve(int N, int order[]){
  total = N;
  for (int i = 1; i <= N; i++) {
    q[0].push(i);
    push_train();
  }
  for(int i = 0;i < N; i++){
    if (i % 2 == 0) {
      cout<<"Target is "<<order[i]<<endl;
      getfromr(order[i]);
    } else {
      getfroml(order[i]);
    }
  }
}

int main(){
  int len = 5;
  for (int i = len; i >= 1; i--) {
    m[0].push(i);
    cout<<i<<' ';
  }
  cout<<endl;
  int od[] = {5,1,4,2,3};
  solve(len,od);
  for (int i = 0; i < len; i++) {
    cout<<m[3].top()<<' ';
    m[3].pop();
  }
}
