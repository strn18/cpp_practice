#include <iostream>
#include <cstring>
#define MAX 10000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int N, x, y;

    int parent[MAX+1];
    bool visited[MAX+1];

    cin >> N;

    memset(parent, 0, sizeof(int) * (N-1));
    memset(visited, false, sizeof(int) * (N-1));

    for(int i=0; i<N-1; i++){
      int a, b;

      cin >> a >> b;

      parent[b] = a;
    }

    cin >> x >> y;

    while(parent[x]){
      visited[x] = true;
      x = parent[x];
    }

    visited[x] = true;

    while(!visited[y]){
      y = parent[y];
    }

    cout << y << '\n';
  }  
  
  return 0;
}

/*
쉬운 LCA 문제. 노드의 수가 적어서 그냥 하나하나 찾는 방식으로 하면 된다.
*/