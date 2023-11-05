#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, num;
  vector<int> arr;

  cin >> N >> M;

  N += M;

  while(N--){
    cin >> num;
    arr.push_back(num);
  }

  sort(arr.begin(), arr.end());

  for(auto e: arr)
    cout << e << ' ';

  return 0;
}