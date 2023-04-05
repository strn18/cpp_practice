#include <iostream>
#include <string>
#define MAX 200000

using namespace std;

int p_sum[MAX][26] = {0};

int main(){
  cin.sync_with_stdio(false); cin.tie(NULL);
  
  char ch;
  int q, left, right;
  string S;

  cin >> S;

  for(int i=0; i<S.size(); i++)
    p_sum[i][S[i]-'a'] = 1;
  
  for(int i=1; i<S.size(); i++)
    for(int j=0; j<26; j++)
      p_sum[i][j] += p_sum[i-1][j];

  cin >> q;

  while(q--){
    cin >> ch >> left >> right;

    if(left == 0)
      cout << p_sum[right][ch-'a'];
    else
      cout << p_sum[right][ch-'a']-p_sum[left-1][ch-'a'];

    cout << '\n';
  }

  return 0;
}