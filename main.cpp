#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  vector<ll> v;

  cin >> N;

  while(N--){
    ll num;

    cin >> num;

    v.push_back(num);
  }

  sort(v.begin(), v.end());

  int maxCount = 1;
  ll maxVal = v[0];

  int curCount = 1;
  ll curVal = v[0];

  for(int i=1; i<v.size(); i++){
    if(v[i] != curVal){
      if(curCount > maxCount){
        maxCount = curCount;
        maxVal = curVal;
      }
      curCount = 1;
      curVal = v[i];
    }
    else{
      curCount++;
    }
  }

  if(curCount > maxCount){
    maxCount = curCount;
    maxVal = curVal;
  }

  cout << maxVal;

  return 0;
}