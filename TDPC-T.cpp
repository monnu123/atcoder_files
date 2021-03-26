#include <bits/stdc++.h>
using namespace std;
//#include <atcoder/all>
//using namespace atcoder;
using ll=long long;
using Graph=vector<vector<int>>;
#define MAX 50
#define MOD 1000000007

int K;
int N;

vector<ll> solve1(vector<ll> &x){
  vector<ll> ret(K);
  ret[0]=x[K-1];
  for(int i=1;i<K;i++){
    ret[i]=x[i-1]+x[K-1];
    ret[i]%=MOD;
  }
  return ret;
}

vector<ll> solve2(vector<ll> &x){
  vector<vector<ll>> xx(K,vector<ll>(K));
  xx[0]=x;
  for(int i=1;i<K;i++){
    xx[i]=solve1(xx[i-1]);
  }
  vector<ll> ret(K,0);
  for(int i=0;i<K;i++){
    for(int j=0;j<K;j++){
      ret[j]+=x[i]*xx[i][j];
      ret[j]%=MOD;
    }
  }
  return ret;
}

int main(){
  cin>>K>>N;
  N--;
  if(N<K){
    cout<<1<<endl;
  }else{
    vector<int> nums;
    while(N>K){
      nums.push_back(N);
      if(N%2==0&&N/2>=K){
        N/=2;
      }else{
        N--;
      }
    }
    reverse(nums.begin(),nums.end());
    int n=nums.size();
    vector<ll> x(K,1);
    int num=K;
    for(int i=0;i<n;i++){
      if(nums[i]==num+1){
        x=solve1(x);
        num=num+1;
      }else{
        x=solve2(x);
        num*=2;
      }
    }

    ll ans=0;
    for(int i=0;i<K;i++){
      ans+=x[i];
    }
    ans%=MOD;
    cout<<ans<<endl;
  }
}
