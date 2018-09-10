vector<ll> pre_hash(MAXN,-1);
ll rolling_hash(string s,ll c,ll md){
  ll sum = 0;
  ll times = 1;
  REP(i,ll(s.size())){
    sum+=(s[i]*times)%md;
    sum%=md;
    times = (times*c)%md;
    pre_hash[i] = sum;
  }
}
