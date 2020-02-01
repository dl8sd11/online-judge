#include "combo.h"
#include <bits/stdc++.h>
using namespace std;
char c[] = {'A','B','X','Y'};

char head() {
  if (press("AB") > 0) {
    if (press("A")) {
      return 'A';
    } else {
      return 'B';
    }
  } else {
    if (press("X")) {
      return 'X';
    } else {
      return 'Y';
    }
  }
}

char tc[3];
std::string guess_sequence(int N) {
  string S;
  int h = head();
  S += h;
  int cnt = 0;
  for (int i=0;i<4;i++) {
    if (c[i] != h) {
      tc[cnt++] = c[i];
    }
  }

  for (int i=1;i<N-1;i++) {
    string q;
    q += S + tc[0];
    for (int j=0;j<3;j++) {
      q += S+tc[1]+tc[j];
    }
    int ret = press(q);
    if (ret == int(S.size())) {
      S += tc[2];
    } else if (ret == int(S.size())+1) {
      S += tc[0];
    } else {
      S += tc[1];
    }
  }

  if (N > 1) {
    for (int i=0;i<2;i++) {
      if (press(S+tc[i]) == N) {
        S += tc[i];
        break;
      }
    }
    if (S.size() != N) {
      S += tc[2];
    }
  }

  return S;
}
