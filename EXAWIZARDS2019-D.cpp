#include <bits/stdc++.h>
using namespace std;
//#include <atcoder/all>
//using namespace atcoder;
using ll=long long;
using Graph=vector<vector<pair<int,int>>>;
#define MAX 200003
#define MOD 1000000007
#define INF 1000000000

int main(){
  int N;
  int X;
  cin>>N>>X;
  vector<ll> S(N);
  for(int i=0;i<N;i++){
    cin>>S[i];
  }
  sort(S.begin(),S.end());

  vector<vector<ll>> dp(N+1,vector<ll>(X+1,0));
  for(int j=1;j<=X;j++){
    dp[1][j]=(ll)j%S[0];
    for(int i=2;i<=N;i++){
      dp[i][j]=dp[i-1][j]*((ll)i-1)+dp[i-1][j%S[i-1]];
      dp[i][j]%=MOD;
    }
  }

  cout<<dp[N][X]<<endl;
}
