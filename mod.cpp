#include <bits/stdc++.h>
using namespace std;
using ll=long long;

#define MAX 200003
#define MOD 1000000007

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




int main(){
  for(int i=1;i<13;i++){
    cout<<i<<" : "<<modinv(i,13)<<endl;
  }
  return 0;
}
