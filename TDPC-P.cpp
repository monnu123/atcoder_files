#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll=long long;
using Graph=vector<vector<int>>;
#define MOD 1000000007
#define INF 2000000000
#define MAX 1000000

int K;
void dfs(Graph &G,int v,int p,vector<vector<ll>> &dp){
  for(auto nv:G[v]){
    if(nv==p){
      continue;
    }
    dfs(G,nv,v,dp);
  }
  if(p!=-1&&G[v].size()==1){
    dp[v][0]=1;
    dp[v][1]=1;
  }else{
    int n=G[v].size();
    vector<vector<vector<ll>>> sum(n+1,vector<vector<ll>>(2*K+1,vector<ll>(3,0)));
    sum[0][0][0]=1;
    sum[0][1][1]=1;
    for(int i=0;i<n;i++){
      if(G[v][i]==p){
        sum[i+1]=sum[i];
        continue;
      }
      int nv=G[v][i];
      for(int j=0;j<=2*K;j++){
        if(j%2==0){
          for(int k=0;k+j<=2*K;k++){
            for(int l=0;l<=2;l++){
              sum[i+1][k+j][l]+=sum[i][k][l]*dp[nv][j];
              sum[i+1][k+j][l]%=MOD;
            }
          }
        }else{
          for(int k=0;k+j<=2*K;k++){
            for(int l=0;l<=1;l++){
              sum[i+1][k+j][l+1]+=sum[i][k][l]*dp[nv][j];
              sum[i+1][k+j][l+1]%=MOD;
            }
          }
        }
      }
    }
    for(int i=0;i<=2*K;i++){
      dp[v][i]=sum[n][i][0]+sum[n][i][1]+sum[n][i][2];
      dp[v][i]%=MOD;
    }
  }
}

int main(){
  int N;
  cin>>N>>K;
  Graph G(N);
  for(int i=0;i<N-1;i++){
    int a,b;
    cin>>a>>b;
    a--;b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  vector<vector<ll>> dp(N,vector<ll>(2*K+1,0));
  dfs(G,0,-1,dp);
  ll ans=dp[0][2*K];
  cout<<ans<<endl;
}
