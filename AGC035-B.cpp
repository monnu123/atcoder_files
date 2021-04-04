#include <bits/stdc++.h>
using namespace std;
//#include <atcoder/all>
//using namespace atcoder;
using ll=long long;
using Graph=vector<vector<int>>;
#define MAX 50
#define MOD 1000000007
#define INF 1000000000

vector<int> A,B;
vector<int> cnt;

void dfs1(Graph &G,int v,int p,vector<bool> &seen,vector<bool> &tree_edge){
  seen[v]=true;
  for(auto e:G[v]){
    int nv=A[e]+B[e]-v;
    if(seen[nv]==true){
      continue;
    }
    tree_edge[e]=true;
    dfs1(G,nv,v,seen,tree_edge);
  }
}

void dfs2(Graph &G,int v,int p,vector<bool> &tree_edge){
  for(auto e:G[v]){
    if(tree_edge[e]==false){
      continue;
    }
    int nv=A[e]+B[e]-v;
    if(nv==p){
      continue;
    }
    dfs2(G,nv,v,tree_edge);
    if(cnt[nv]%2==1){
      cnt[nv]++;
      cout<<nv+1<<" "<<v+1<<endl;
    }else{
      cnt[v]++;
      cout<<v+1<<" "<<nv+1<<endl;
    }
  }
}

int main(){
  int N,M;
  cin>>N>>M;

  Graph G(N);
  A.resize(M);
  B.resize(M);
  for(int i=0;i<M;i++){
    cin>>A[i]>>B[i];
    A[i]--;B[i]--;
    G[A[i]].push_back(i);
    G[B[i]].push_back(i);
  }

  if(M%2==1){
    cout<<-1<<endl;
    return 0;
  }
  vector<bool> seen(N,false);
  vector<bool> tree_edge(M,false);
  dfs1(G,0,-1,seen,tree_edge);
  cnt.resize(N,0);
  for(int i=0;i<M;i++){
    if(tree_edge[i]==false){
      cout<<A[i]+1<<" "<<B[i]+1<<endl;
      cnt[A[i]]++;
    }
  }

  dfs2(G,0,-1,tree_edge);

}
