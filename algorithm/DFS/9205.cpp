#include <iostream>
#include <cstring>
#include <cmath>
#define MAX 100

using namespace std;

typedef struct {int r, c;} pos;

int n;
pos dest, node[MAX+1];
bool visited[MAX+1];

bool dfs(int cur);
bool checkDist(pos a, pos b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    cin >> n;

    for(int i=0; i<n+1; i++)
      cin >> node[i].r >> node[i].c;
    
    cin >> dest.r >> dest.c;

    memset(visited, false, sizeof(bool)*(n+1));

    if(dfs(0)) cout << "happy\n";
    else cout << "sad\n";
  }

  return 0;
}

bool dfs(int cur){
  visited[cur] = true;

  if(checkDist(node[cur], dest)) return true;

  for(int i=0; i<n+1; i++){
    if(checkDist(node[cur], node[i]) && !visited[i]){
      if(dfs(i)) return true;
    }
  }

  return false;
}

bool checkDist(pos a, pos b){
  if( abs(a.r - b.r) + abs(a.c - b.c) <= 1000 ) return true;
  else return false;
}

/*
문제 설명을 좀 복잡하게 꼬아놨는데, 그냥 어떠한 노드에서 갈 때, 주위 노드 중 거리가 1000 이하인 노드로만 갈 수 있다. 그렇게 가서 결국 목적지에 
도착할 수 있는지를 판단하면 됨. 나는 dfs로 풀었는데, 백준은 bfs로 분류되어있음. 다른 풀이 보니까 bfs가 좀 더 깔끔해보이기는 한다. 
*/