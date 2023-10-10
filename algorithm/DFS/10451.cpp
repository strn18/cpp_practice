#include <iostream>
#include <cstring>
#define MAX 1000

using namespace std;

int edge[MAX+1];
bool visited[MAX+1];

void visit(int v);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int N, cycles = 0;

    cin >> N;

    memset(visited, false, sizeof(bool)*(N+1));

    for(int i=1; i<=N; i++)
      cin >> edge[i];

    for(int i=1; i<=N; i++){
      if(!visited[i]){
        cycles++;
        visit(i);
      }
    }

    cout << cycles << '\n';
  }

  return 0;
}

void visit(int v){
  visited[v] = true;

  if(!visited[edge[v]]) visit(edge[v]);
}

/*
백준 분류는 순열 사이클 분할이라고 하는데 그냥 dfs로 분류함. 
*/