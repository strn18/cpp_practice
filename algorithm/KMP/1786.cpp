#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#define MAX 1000000

using namespace std;

int fail[MAX];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string T, P;
  int tSize, pSize;
  vector<int> pos;

  getline(cin, T);
  getline(cin, P);

  tSize = T.size();
  pSize = P.size();

  memset(fail, 0, sizeof(int)*pSize);

  for(int i=1, j=0; i<pSize; i++){
    while(P[i] != P[j] && j > 0) j = fail[j-1];

    if(P[i] == P[j]){
      fail[i] = j+1;
      
      j++;
    }
  }

  for(int i=0, j=0; i<tSize; i++){
    while(T[i] != P[j] && j > 0) j = fail[j-1];

    if(T[i] == P[j]){
      if(j == pSize-1){
        pos.push_back(i - pSize + 2);
        j = fail[j];
      }
      else j++;
    }
  }

  cout << pos.size() << '\n';

  for(int i=0; i<pos.size(); i++)
    cout << pos[i] << ' ';
  
  return 0;
}

/*
딱 기본적인 KMP 문제.
*/