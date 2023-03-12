#include <iostream>
#include <vector>
#define MAX 2000

using namespace std;

vector<int> adj[MAX];
bool visited[MAX] = {0};

bool search(int start, int n); // start를 시작으로, 깊이 n인 친구 관계가 있으면 true

int main(){
  int N, M, a, b;

  scanf("%d %d", &N, &M);

  for(int i=0; i<M; i++){
    scanf("%d %d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for(int i=0; i<N; i++){
    if(search(i, 4)){
      printf("1");

      return 0;
    }
  }

  printf("0");

  return 0;
}

bool search(int start, int n){
  if(n == 0) return true;

  visited[start] = true;

  for(int i=0; i<adj[start].size(); i++){
    int next = adj[start][i];

    if(!visited[next])
      if(search(next, n-1))
        return true;
  }

  visited[start] = false;

  return false;
}