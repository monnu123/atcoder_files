#include <bits/stdc++.h>
using namespace std;


//同じ数字を含むときは先にくるものが小さい
template<class T>
class CartesianTree{
private:
  int n;
  vector<T> a;
  vector<int>left,right,parent;
  int root;
  void dfs(int v,int l,int r){
    if(left[v]!=-1){
      dfs(left[v],l,v);
    }
    //操作
    if(right[v]!=-1){
      dfs(right[v],v+1,r);
    }
  }
public:
  CartesianTree(vector<T> a_):a(a_){
    int n=a.size();
    left.resize(n,-1);
    right.resize(n,-1);
    for(int i=1;i<n;i++){
      int j=i-1;
      while(parent[j]!=-1&&a[j]>a[i]){
        j=parent[j];
      }
      if(parent[j]==-1&&a[j]>a[i]){
        parent[j]=i;
        left[i]=j;
        root=i;
      }else{
        int ch=right[j];
        right[j]=i;
        parent[i]=j;
        left[i]=ch;
        if(ch!=-1){
          parent[ch]=i;
        }
      }
    }
  }
  void insert(T x){
    a.push_back(x);
    left.push_back(-1);
    right.push_back(-1);
    parent.push_back(-1);
    int i=n;
    n++;
    int j=i-1;
    while(parent[j]!=-1&&a[j]>a[i]){
      j=parent[j];
    }
    if(parent[j]==-1&&a[j]>a[i]){
      parent[j]=i;
      left[i]=j;
      root=i;
    }else{
      int ch=right[j];
      right[j]=i;
      parent[i]=j;
      left[i]=ch;
      if(ch!=-1){
        parent[ch]=i;
      }
    }
  }
  //eulerTourして何らかの操作
  void EulerTour(){
    int v=root;
    dfs(v,0,n);
  }
};


int main(){

}
