#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll=long long;
using Graph=vector<vector<int>>;
#define MOD 1000000007
#define INF 1000000000
#define MAX 1000000

int dfs2(vector<int> &A,vector<int> &index0,vector<int> &index1,int j){
  if(index0.size()==0||index1.size()==0){
    return (1<<30);
  }
  if(j<0){
    return A[index0[0]]^A[index1[0]];
  }
  vector<int> index00,index01;
  vector<int> index10,index11;
  for(auto i:index0){
    if(((A[i]>>j)&1)==0){
      index00.push_back(i);
    }else{
      index01.push_back(i);
    }
  }
  for(auto i:index1){
    if(((A[i]>>j)&1)==0){
      index10.push_back(i);
    }else{
      index11.push_back(i);
    }
  }
  int ret=1<<30;
  ret=min(ret,dfs2(A,index00,index10,j-1));
  ret=min(ret,dfs2(A,index01,index11,j-1));
  if((index00.size()==0||index10.size()==0)&&(index01.size()==0||index11.size()==0)){
    ret=min(ret,dfs2(A,index00,index11,j-1));
    ret=min(ret,dfs2(A,index01,index10,j-1));
  }
  return ret;
}

int dfs1(vector<int> &A,vector<int> &index,int j){
  if(index.size()==0){
    return 0;
  }
  if(j<0){
    return 0;
  }
  vector<int> index0;
  vector<int> index1;
  for(auto i:index){
    if(((A[i]>>j)&1)==0){
      index0.push_back(i);
    }else{
      index1.push_back(i);
    }
  }
  if(index0.size()%2==0){
    int ret=max(dfs1(A,index0,j-1),dfs1(A,index1,j-1));
    return ret;
  }else{
    int ret=dfs2(A,index0,index1,j-1);
    return ret;
  }
}

int main(){
  int N;
  cin>>N;
  vector<int> A(2*N);
  vector<int> index(2*N);
  for(int i=0;i<2*N;i++){
    index[i]=i;
    cin>>A[i];
  }
  int ans=dfs1(A,index,30);
  cout<<ans<<endl;
}
