#include <iostream>
#include <string>
#include <algorithm>
#define MAX 1000

using namespace std;

int main(){
  string S;
  string suffix[MAX];

  cin >> S;

  for(int i=0; i<S.size(); i++)
    for(int j=0; j<=i; j++)
      suffix[j].push_back(S[i]);

  sort(suffix, suffix+S.size());

  for(int i=0; i<S.size(); i++)
    cout << suffix[i] << '\n';

  return 0;
}