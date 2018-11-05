#include <bits/stdc++.h>
using namespace std;
int main()
{
  string s;
  vector< pair<string,int> > v[1000];
  map<string,vector< pair<string,int> >> m;
  m[s] = v;
  for(map<string,vector< pair<string,int> >>::iterator it=m.begin();it<=m.end();it++)
    cout<<it.first;
  }
