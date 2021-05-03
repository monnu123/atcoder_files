#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
using ll=long long;

class Matrix{
  int H,W;
  vector<vector<ll>> a;
  ll modpow(ll a,ll x){
    ll ret=1;
    a%=MOD;
    while(x>0){
      if(x%2==1){
        ret=a*ret%MOD;
      }
      x>>=1;
      a=a*a%MOD;
    }
    return ret;
  }
  ll modinv(ll x){
    return modpow(x,MOD-2);
  }
public:
  vector<ll>& operator[](int i){
    return a[i];
  }
  Matrix(vector<vector<ll>> a_):a(a_),H(a_.size()),W(a_[0].size()){}
  Matrix(int h,int w):H(h),W(w),a(h,vector<ll>(w,0)){}
  Matrix operator * (Matrix other){
    assert(W==other.H);
    int h=H;
    int w=other.W;
    Matrix ret(h,w);
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++){
        for(int k=0;k<W;k++){
          ret.a[i][j]+=a[i][k]*other.a[k][j]%MOD;
        }
        ret.a[i][j]%=MOD;
      }
    }
    return ret;
  }
  Matrix operator + (Matrix other){
    assert(H==other.H&&W==other.W);
    int h=H;
    int w=W;
    Matrix ret(h,w);
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++){
        ret.a[i][j]=(a[i][j]+other.a[i][j])%MOD;
      }
    }
    return ret;
  }
  ll det(){
    assert(H==W);
    int N=H;
    vector<vector<ll>> b=a;
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        b[i][j]%=MOD;
      }
    }
    for(int i=0;i<N;i++){
      if(b[i][i]==0){
        bool flag=false;
        for(int j=i+1;j<N;j++){
          if(b[j][i]!=0){
            flag=true;
            swap(b[i],b[j]);
            break;
          }
          if(flag==false){
            return 0;
          }
        }
      }
      for(int k=i+1;k<N;k++){
        if(b[k][i]!=0){
          ll x=b[k][i]*modinv(b[i][i])%MOD;
          for(int j=0;j<N;j++){
            b[k][j]=(b[k][j]-x*b[i][j]%MOD+MOD)%MOD;
          }
        }
      }
    }
    ll ret=1;
    for(int i=0;i<N;i++){
      ret=ret*b[i][i]%MOD;
    }
    return ret;
  }

  Matrix inv(){
    assert(H==W);
    assert(det()!=0);
    int N=H;
    vector<vector<ll>> ret(N,vector<ll>(N,0));
    for(int i=0;i<N;i++){
      ret[i][i]=1;
    }
    vector<vector<ll>> b=a;
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        b[i][j]%=MOD;
      }
    }
    for(int i=0;i<N;i++){
      if(b[i][i]==0){
        bool flag=false;
        for(int j=i+1;j<N;j++){
          if(b[j][i]!=0){
            flag=true;
            swap(b[i],b[j]);
            swap(ret[i],ret[j]);
            break;
          }
        }
      }
      for(int k=0;k<N;k++){
        if(k==i){
          continue;
        }
        if(b[k][i]!=0){
          ll x=b[k][i]*modinv(b[i][i])%MOD;
          for(int j=0;j<N;j++){
            b[k][j]=(b[k][j]-x*b[i][j]%MOD+MOD)%MOD;
            ret[k][j]=(ret[k][j]-x*ret[i][j]%MOD+MOD)%MOD;
          }
        }
      }
    }
    for(int i=0;i<N;i++){
      ll x=modinv(b[i][i]);
      for(int j=0;j<N;j++){
        b[i][j]=b[i][j]*x%MOD;
        ret[i][j]=ret[i][j]*x%MOD;
      }
    }
    Matrix c(ret);
    return c;
  }
};

int main(){
  int N;
  cin>>N;
}
