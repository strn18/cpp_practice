#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  int box[MAX];
  vector<int> v;

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> box[i];

  v.push_back(box[0]);

  for(int i=1; i<N; i++){
    if(box[i] > v.back()) v.push_back(box[i]);
    else{
      int idx = lower_bound(v.begin(), v.end(), box[i]) - v.begin();
      v[idx] = box[i];
    }
  }

  cout << v.size();

  return 0;
}