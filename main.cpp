#include <iostream>
#include <map>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, X;
  map<int, int> m; // {key값, depth}
  long long C = 0;

  cin >> N;

  m.insert({0, 0});
  m.insert({N+1, 0});

  for(int i=0; i<N; i++){
    int depth;

    cin >> X;

    map<int, int>:: iterator higher_min = m.lower_bound(X);
    map<int, int>:: iterator lower_max = (--higher_min)++;

    depth = max(higher_min->second, lower_max->second)+1;

    m.insert({X, depth});
    C += depth-1;

    cout << C << '\n';
  }

  return 0;
}