#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000

using namespace std;

int parent[MAX];

int findRoot(int x);
bool unionRoot(int x, int y);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, flowCount = 0;
  long long costCount = 0;
  vector<pair<int, pair<int, int>>> edge;

  cin >> N;

  for(int i=0; i<N; i++){
    parent[i] = i;

    for(int j=0; j<N; j++){
      int c;

      cin >> c;

      if(i < j) edge.push_back({c, {i, j}});
    }
  }

  sort(edge.begin(), edge.end());

  for(int i=0; flowCount < N-1; i++){
    int cost = edge[i].first;
    int x = edge[i].second.first;
    int y = edge[i].second.second;

    if(unionRoot(x, y)){
      costCount += cost;
      flowCount++;
    }
  }

  cout << costCount;

  return 0;
}

int findRoot(int x){
  if(parent[x] == x) return x;
  else return parent[x] = findRoot(parent[x]);
}

bool unionRoot(int x, int y){
  int rx = findRoot(x);
  int ry = findRoot(y);

  if(rx == ry) return false;

  parent[ry] = rx;

  return true;
}

/*
그냥 MST 문제. 크루스칼 사용했음. costCount를 long long으로 안 해서 한 번 틀렸다. 그리고 행렬이 입력으로 돌아오는데, 어차피 (i, j)와 (j, i)의 
값(cost)은 같기에 굳이 중복해서 edge에 push할 필요가 없다. 31행과 같이, 둘 중 하나만 push하도록 했더니 시간이랑 메모리 줄어듦. 
*/