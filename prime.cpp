#include <bits/stdc++.h>
using namespace std;
#define MAX 40000000
vector<int> p;
vector<bool> p_table(MAX+1,true);
void prime(){
  p_table.at(0)=false,p_table.at(1)=false;
  for(int i=2;i<=MAX;i++){
    if(p_table.at(i)){
      p.push_back(i);
      for(int j=2;i*j<=MAX;j++){
        p_table.at(i*j)=false;
      }
    }
  }
}



int main(){
  prime();
  cout<<p.size()<<endl;
}
