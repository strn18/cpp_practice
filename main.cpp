#include <iostream>
#include <algorithm>
#include <cstdlib>
#define MAX 100000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, val[MAX];
  int ans, left, right;

  cin >> N;
  for(int i=0; i<N; i++)
    cin >> val[i];

  sort(val, val+N);

  int l = 0, r = N-1;
  ans = abs(val[l]+val[r]);
  left = l; right = r;

  while(l != r-1){
    if(abs(val[l+1]+val[r]) < abs(val[l]+val[r-1]))
      l++;
    else
      r--;

    if(abs(val[l]+val[r]) < ans){
      ans = abs(val[l]+val[r]);
      left = l; right = r;
    }
  }

  cout << val[left] << ' ' << val[right];

  return 0;
}