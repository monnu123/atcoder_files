#include <bits/stdc++.h>
using namespace std;
#define MAX_V 300
#define INF 1000000000

struct Edge{
  int to,cap,rev;
};

vector<Edge> G[MAX_V];
int level[MAX_V];
int iter[MAX_V];

void add_edge(int from,int to,int cap){
  int n=G[to].size();
  int m=G[from].size();
  G[from].push_back((Edge){to,cap,n});
  G[to].push_back((Edge){from,0,m});
}

void bfs(int s){
  memset(level,-1,sizeof(level));
  queue<int> que;
  level[s]=0;
  que.push(s);
  while(!que.empty()){
    int v=que.front();
    que.pop();
    for(int i=0;i<G[v].size();i++){
      Edge &e=G[v][i];
      if(e.cap>0&&level[e.to]<0){
        level[e.to]=level[v]+1;
        que.push(e.to);
      }
    }
  }
}

int dfs(int v,int t,int f){
  if(v==t){
    return f;
  }
  for(int &i=iter[v];i<G[v].size();i++){
    Edge &e=G[v][i];
    if(e.cap>0&&level[v]<level[e.to]){
      int d=dfs(e.to,t,min(f,e.cap));
      if(d>0){
        e.cap-=d;
        G[e.to][e.rev].cap+=d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s,int t){
  int flow=0;
  for(;;){
    bfs(s);
    if(level[t]<0){
      return flow;
    }
    memset(iter,0,sizeof(iter));
    int f;
    while((f=dfs(s,t,INF))>0){
      flow+=f;
    }
  }
}


int main(){
  int N,G,E;
  cin>>N>>G>>E;
  vector<int> p(G);
  for(int i=0;i<G;i++){
    cin>>p[i];
  }
  for(int i=0;i<E;i++){
    int a,b;
    cin>>a>>b;
    add_edge(a,b,1);
    add_edge(b,a,1);
  }
  for(int i=0;i<G;i++){
    add_edge(p[i],N,1);
  }

  cout<<max_flow(0,N)<<endl;


}
