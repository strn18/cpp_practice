#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 1000000

using namespace std;

int arr[MAX];
vector<int> v; // v[i]: arr로부터 길이가 i+1인 LIS를 만들 때, 마지막(가장 큰) 수.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> arr[i];
  
  v.push_back(arr[0]);

  for(int i=1; i<N; i++){
    if(arr[i] > v.back()){
      v.push_back(arr[i]);
    }
    else{
      int idx = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
      v[idx] = arr[i];
    }
  }

  cout << v.size();

  return 0;
}