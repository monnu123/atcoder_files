#include <bits/stdc++.h>
using namespace std;
using ll=long long;

template <class T>
class bit_base{
  int n=0;
  vector<T> vec;
public:
  bit_base(){}
  void add(T x){
    int k;
    for(int i=0;i<n;i++){
      k=0;
      while(((vec[i]>>k)&1)==0){
        k++;
      }
      if(((x>>k)&1)==1){
        x^=vec[i];
      }
    }
    if(x==0){
      return;
    }
    k=0;
    while(((x>>k)&1)==0){
      k++;
    }
    for(int i=0;i<n;i++){
      if(((vec[i]>>k)&1)==1){
        vec[i]^=x;
      }
    }
    for(int i=0;i<n;i++){
      T a=x^(-x);
      T b=vec[i]^(-vec[i]);
      if(a<b){
        vec.insert(vec.begin()+i,x);
        ++n;
        return;
      }
    }
    vec.insert(vec.begin()+n,x);
    ++n;
    return;
  }
  int contain(T x){
    int k;
    for(int i=0;i<n;i++){
      k=0;
      while(((vec[i]>>k)&1)==0){
        k++;
      }
      if(((x>>k)&1)==1){
        x^=vec[i];
      }
    }

    if(x==0){
      return 1;
    }else{
      return 0;
    }
  }
};

void solve(){
  int N;
  cin>>N;
  vector<ll> A(N);
  for(int i=0;i<N;i++){
    cin>>A[i];
  }
  string S;
  cin>>S;

  bit_base<ll> a;
  for(int i=N-1;i>=0;i--){
    if(S[i]=='0'){
      a.add(A[i]);
    }else{
      if(a.contain(A[i])==0){
        cout<<1<<'\n';
        return;
      }
    }
  }
  cout<<0<<'\n';
  return;
}

int main(){
  int T;
  cin>>T;
  for(int i=0;i<T;i++){
    solve();
  }
}
