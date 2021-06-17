#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll=long long;
#define MOD 998244353
using Graph=vector<vector<int>>;
#define INF 1000000000
#define MAX 300000

vector<int> parent;
vector<int> sign;
vector<ll> V;
int find(int x){
  int y=parent[x];
  if(y!=parent[y]){
    int pre_y=y;
    y=find(y);
    sign[x]=sign[pre_y]*sign[x]*(-1);
    V[x]=V[pre_y]+V[x]*(ll)sign[pre_y]*(-1);
  }
  return parent[x]=y;
}
void unite(int a,int b,ll v){
  int x=find(a);
  int y=find(b);
  if(x!=y){
    if(x==a&&b==y){
      sign[y]=1;
      V[y]=v;
    }else if(b==y){
      if(sign[a]==1){
        sign[b]=-1;
        V[b]=V[a]-v;
      }else{
        sign[b]=1;
        V[b]=V[a]+v;
      }
    }else if(x==a){
      if(sign[b]==1){
        sign[y]=-1;
        V[y]=v-V[b];
      }else{
        sign[y]=1;
        V[y]=v+V[b];
      }
    }else{
      if(sign[a]==1&&sign[b]==1){
        sign[y]=1;
        V[y]=V[a]-v+V[b];
      }else if(sign[a]==1&&sign[b]==-1){
        sign[y]=-1;
        V[y]=V[a]-v-V[b];
      }else if(sign[a]==-1&&sign[b]==1){
        sign[y]=-1;
        V[y]=V[a]+v-V[b];
      }else{
        sign[y]=1;
        V[y]=V[a]+v+V[b];
      }
    }
    parent[y]=x;
  }
}

int main(){
  int N,Q;
  cin>>N>>Q;
  parent.resize(N);
  sign.resize(N,0);
  V.resize(N);
  for(int i=0;i<N;i++){
    parent[i]=i;
  }
  for(int i=0;i<Q;i++){
    int t,x,y,v;
    cin>>t>>x>>y>>v;
    x--;y--;
    if(t==0){
      if(find(x)!=find(y)){
        if(x>y){
          swap(x,y);
        }
        unite(x,y,v);
      }
    }else{
      if(find(x)==find(y)){
        if(x==y){
          cout<<v<<endl;
        }else if(x==find(x)){
          if(sign[y]==1){
            cout<<V[y]-v<<endl;
          }else{
            cout<<-V[y]+v<<endl;
          }
        }else if(y==find(y)){
          if(sign[x]==1){
            cout<<V[x]-v<<endl;
          }else{
            cout<<V[x]+v<<endl;
          }
        }else{
          if(sign[x]==1&&sign[y]==1){
            cout<<V[y]-V[x]+v<<endl;
          }else if(sign[x]==-1&&sign[y]==-1){
            cout<<V[x]-V[y]+v<<endl;
          }else if(sign[x]==1&&sign[y]==-1){
            cout<<V[x]-V[y]-v<<endl;
          }else if(sign[x]==-1&&sign[y]==1){
            cout<<V[y]-V[x]-v<<endl;
          }
        }
      }else{
        cout<<"Ambiguous"<<endl;
      }
    }
  }
}
