#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll=long long;
using Graph=vector<vector<int>>;
#define MOD 1000000007
#define INF 2000000000
#define MAX 1000000

ll modpow(ll a,ll n,ll mod){
  ll res=1;
  while(n>0){
    if(n&1){       //nのbitと...00001を比較  nが2で割り切れるならtrue
      res=(res*a)%mod;
    }
    a=(a*a)%mod;
    n>>=1;
  }
  return res;
}

ll modinv(ll a,ll mod){
  return modpow(a,mod-2,mod);
}

ll fac[MAX],finv[MAX],inv[MAX];

void COMinit(){
  fac[0]=fac[1]=1;
  finv[0]=finv[1]=1;
  inv[1]=1;
  for(int i=2;i<MAX;i++){
    fac[i]=(fac[i-1]*i)%MOD;
    inv[i]=MOD-inv[MOD%i]*(MOD/i)%MOD;
    finv[i]=finv[i-1]*inv[i]%MOD;
  }
}

ll COM(int n,int k){
  if(n<k){
    return 0;
  }
  if(n<0||k<0){
    return 0;
  }
  return fac[n]*(finv[k]*finv[n-k]%MOD)%MOD;
}


ll dfs(Graph &G,int v,int p,vector<int> &sz){
  ll ret=1;
  sz[v]=0;
  for(auto nv:G[v]){
    if(nv==p){
      continue;
    }
    ret*=dfs(G,nv,v,sz);
    ret%=MOD;

    sz[v]+=sz[nv]+1;
    ret*=finv[sz[nv]+1];
    ret%=MOD;
  }
  ret*=fac[sz[v]];
  ret%=MOD;
  return ret;
}

int main(){
  int N;
  cin>>N;
  Graph G(N);
  vector<int> a(N-1),b(N-1);
  for(int i=0;i<N-1;i++){
    cin>>a[i]>>b[i];
    a[i]--;
    b[i]--;
    G[a[i]].push_back(b[i]);
    G[b[i]].push_back(a[i]);
  }
  COMinit();

  ll ans=0;
  for(int i=0;i<N-1;i++){
    vector<int> sz(N,0);
    ll x=dfs(G,a[i],b[i],sz)*dfs(G,b[i],a[i],sz)%MOD;
    ll y=(fac[N-2]*finv[sz[a[i]]]%MOD)*finv[sz[b[i]]]%MOD;
    ans+=x*y;
    ans%=MOD;
  }
  cout<<ans<<endl;
}
