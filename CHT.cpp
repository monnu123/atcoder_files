#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll INF=1000000000000000000;

//傾きが単調減少
//最小値を求める
//bool sorted:xが単調増加
template<class T>
class CHT{
  struct Line{
    T a,b;
    Line(ll a_,ll b_):a(a_),b(b_){}
    Line():a(0),b(0){}
    T get(T x){
      return a*x+b;
    }
  };
private:
  int n;
  int s,t;
  bool sorted;
  vector<Line> deq;
  bool check(Line &l1,Line &l2,Line &l3) const{
    return (l2.a-l1.a)*(l3.b-l2.b)<(l2.b-l1.b)*(l3.a-l2.a);
  }
public:
  //直線の最大数
  CHT(int n_,bool flag=true):n(n_),s(0),t(0),deq(n),sorted(flag){}
  void insert(T a,T b){
    Line l3(a,b);
    while(t-s>=2){
      Line l1=deq[t-2];
      Line l2=deq[t-1];
      if(check(l1,l2,l3)){
        break;
      }
      t--;
    }
    deq[t]=l3;
    t++;
  }
  T get(T x){
    if(sorted==true){
      while(t-s>=2){
        Line l1=deq[s];
        Line l2=deq[s+1];
        if(l1.get(x)<l2.get(x)){
          break;
        }
        s++;
      }
      Line l=deq[s];
      return l.get(x);
    }else{
      int left=s;
      int right=t;
      while(left+2<right){
        int c=(left+right)/2;
        if(deq[c].get(x)>deq[c+1].get(x)){
          left=c;
        }else{
          right=c;
        }
      }
      T ret=min<T>(deq[left].get(x),deq[right-1].get(x));
      if(right<t){
        ret=min<T>(ret,deq[right].get(x));
      }
      return ret;
    }
  }
};
