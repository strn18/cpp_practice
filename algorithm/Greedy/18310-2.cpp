#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  vector<int> pos;

  cin >> N;

  for(int i=0; i<N; i++){
    int p;

    cin >> p;

    pos.push_back(p);
  }

  sort(pos.begin(), pos.end());

  cout << pos[ (pos.size() - 1) / 2];

  return 0;
}