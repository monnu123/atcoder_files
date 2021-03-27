#include <bits/stdc++.h>
using namespace std;
using ll=long long;
//gcd(a,b)=a*x-byの解(x1,y1)を返す
// or 1=a*x-byの解、解がなければ(0,0)を返す。
//一般解 (x,y)=(b/gcd(a,b)*t+x1,a/gcd(a,b)*t+y1)
pair<ll,ll> solve_equation(ll a,ll b){
  vector<ll> p,q,r,d;
  p.push_back(a);
  q.push_back(b);
  d.push_back(a/b);
  r.push_back(a%b);
  ll i=0;
  while(r[i]>0){
    p.push_back(q[i]);
    q.push_back(r[i]);
    d.push_back(q[i]/r[i]);
    r.push_back(q[i]%r[i]);
    i++;
  }
  ll gcd=q[i];
  if(q[i]!=1)return make_pair(0,0);
  i--;
  ll aa=1;
  ll bb=1;
  ll cc=0;
  while(i>0){
    i--;
    ll tmp=-bb*d[i+1]-cc;
    cc=-aa;
    aa=tmp;
    bb=tmp;
  }
  ll t;
  if(aa>0){
    t=aa/(b/gcd);
  }else{
    t=(-aa)/(b/gcd)+1;
  }
  return make_pair(aa+(b/gcd)*t,bb*d[i]+cc+(a/gcd)*t);
}

int main(){
  pair<ll,ll> a=solve_equation(4979371,4143);
  cout<<a.first<<" "<<a.second<<endl;
}
