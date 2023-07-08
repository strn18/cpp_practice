#include <iostream>
#include <vector>
#define MAX 50

using namespace std;

int parent[MAX+1];

void union_root(int x, int y);
int find_root(int x); // root가 0이면 진실을 아는 사람임

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, T, count = 0;
  vector<int> party[MAX];

  cin >> N >> M >> T;

  for(int i=1; i<=N; i++)
    parent[i] = i;
  
  for(int i=0; i<T; i++){
    int num;
    cin >> num;
    parent[num] = 0;
  }

  for(int i=0; i<M; i++){
    int n;
    cin >> n;

    for(int j=0; j<n; j++){
      int num;
      cin >> num;
      party[i].push_back(num);
    }

    for(int j=1; j<party[i].size(); j++)
      union_root(party[i][j-1], party[i][j]);
  }

  for(int i=0; i<M; i++)
    if(find_root(party[i][0]) != 0) count++;

  cout << count;

  return 0;
}

void union_root(int x, int y){
  int rx = find_root(x);
  int ry = find_root(y);

  if(rx < ry) parent[ry] = rx;
  else parent[rx] = ry;
}

int find_root(int x){
  if(parent[x] == x) return x;

  return parent[x] = find_root(parent[x]);
}