#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
using ll=long long;

ll modpow(ll a,ll x){
  ll ret=1;
  a%=MOD;
  while(x>0){
    if(x%2==1){
      ret*=a;
      ret%=MOD;
    }
    a=a*a;
    a%=MOD;
    x>>=1;
  }
  return ret;
}

ll inv(ll a){
  return modpow(a,MOD-2);
}

struct Polynomial{
  int n;
  vector<ll> a;
  Polynomial(int V):n(V){
    a.resize(n+1,0);
  }
  Polynomial(vector<ll> b){
    a=b;
    n=a.size()-1;
  }
  ll calc(ll x){
    ll ret=0;
    for(ll i=0;i<=n;i++){
      ret+=a[i]*modpow(x,i)%MOD;
      ret%=MOD;
    }
    return ret;
  }
  Polynomial differentiate(){
    Polynomial P(n-1);
    for(ll i=0;i<=n-1;i++){
      P.a[i]=a[i+1]*(i+1)%MOD;
    }
    return P;
  }
  Polynomial integrate(){
    Polynomial P(n+1);
    for(ll i=0;i<=n;i++){
      P.a[i+1]=a[i]*inv(i+1)%MOD;
    }
    return P;
  }
  //高速化可能(?)
  Polynomial operator*(const Polynomial &other){
    Polynomial P(n+other.n);
    for(int i=0;i<=n;i++){
      for(int j=0;j<=other.n;j++){
        P.a[i+j]+=a[i]*other.a[j]%MOD;
        P.a[i+j]%=MOD;
      }
    }
    return P;
  }

  void print(){
    for(int i=0;i<=n;i++){
      cout<<i<<" : "<<a[i]<<'\n';
    }
    cout<<'\n';
  }
};



int main(){
  int N;
  cin>>N;
  vector<ll> L(N),R(N);
  set<ll> s;
  ll L_max=0;
  for(int i=0;i<N;i++){
    cin>>L[i]>>R[i];
    s.insert(L[i]);
    s.insert(R[i]);
    L_max=max<ll>(L_max,L[i]);
  }
  vector<ll> a;
  for(auto x:s){
    a.push_back(x);
  }
  sort(a.begin(),a.end());
  int n=a.size();
  ll ans=0;
  for(int i=0;i<n-1;i++){
    if(a[i+1]<=L_max){
      continue;
    }
    Polynomial P(0);
    P.a[0]=1;
    for(int j=0;j<N;j++){
      if(a[i]<R[j]){
        vector<ll> b(2);
        b[0]=(MOD-L[j]*inv(R[j]-L[j])%MOD)%MOD;
        b[1]=inv(R[j]-L[j]);
        Polynomial Q(b);
        P=P*Q;
      }
    }
    //P.print();
    P=P.differentiate();
    //P.print();
    Polynomial Q(1);
    Q.a[1]=1;
    P=P*Q;
    //P.print();
    P=P.integrate();
    //P.print();
    ll x=P.calc(a[i+1])-P.calc(a[i])+MOD;
    x%=MOD;
    ans+=x;
    ans%=MOD;
  }
  for(int i=1;i<=N+1;i++){
    ans*=(ll)i;
    ans%=MOD;
  }
  for(int i=0;i<N;i++){
    ans*=R[i]-L[i];
    ans%=MOD;
  }

  cout<<ans<<endl;

}
