#include <bits/stdc++.h>
using namespace std;

vector<int> KMP(string text,string word){
  int N=text.size();
  int m=word.size();
  vector<int> matching_table(m+1);
  matching_table[0]=-1;
  matching_table[1]=0;
  int i=2;
  int j=0;
  while(i<=m){
    if(word[i-1]==word[j]){
      T[i]=j+1;
      i++;
      j++;
    }else if(j>0){
      j=T[j];
    }else{
      T[i]=0;
      i++;
    }
  }

  i=0;
  j=0;
  vector<int> ans;
  while(j+i<N){
    if(word[i]==text[j+i]){
      i++;
      if(i==m){
        ans.push_back(j-m);
      }
    }else{
      j=j+i-matching_table[i];
      if(i>0){
        i=T[i];
      }
    }
  }
  return ans;
}
