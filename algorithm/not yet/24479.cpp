/*
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int visited[100001] = {0};
vector<int> E[100001];

int cur_rank = 1;
int ranking[100001] = {0};

void dfs(int R);

int main(){
  int N, M, R, u, v;
  scanf("%d %d %d", &N, &M, &R);

  for(int i=0; i<M; i++){
    cin >> u >> v;
    E[u].push_back(v);    
    if(u!=v)
      E[v].push_back(u);    
  }

  dfs(R);

  for(int i=1; i<=N; i++)
    printf("%d\n", ranking[i]);

  return 0;
}

void dfs(int R){
  visited[R] = 1;
  sort(E[R].begin(), E[R].end());
  ranking[R] = cur_rank++;

  for(int i=0; i<E[R].size(); i++)
    if(!visited[E[R][i]])
      dfs(E[R][i]);
}

dfs 문제 찾다가 푼 문젠데 실2딱이라 쉬울 줄 알았는데 좀 오래 걸림 ㅅㅂ
사실 문제 자체는 그리 어렵지 않았다. 그냥 벡터 만들어서 (u, v) 간선 정보를 u인덱스에 넣고 그거 방향 반대로 해서 (v, u)를 v인덱스에 넣는 거랑, dfs 내부에서 방문 순서를 오름차순으로 하기 위해 정렬 한번 해주는 거, 그리고 순서 출력을 위해 ranking 배열 만들고 1씩 증가하면서 기록해주고 마지막에 출력하는 거 빼면 딱히 떠올릴 것도 없었음(애초에 문제에 dfs 수도 코드도 있었다). 근데 씨이발 자꾸 시간 초과가 나서 아니 sort를 dfs 안에서 한 게 문제인가? 하고 애초에 간선 입력받을 때 삽입정렬로 미리 정렬해두는 방식도 해봤는데 안 됐고, 뭐지 그럼 dfs를 정직하게 돌리는게 문제인가? 했는데 dfs 시간복잡도는 (정점 수+간선 수)따리라서 시간 초과가 날리가 없고.. 해서 존나 고민했는데, 문제는 그냥 입출력이었다. cin cout endl 얘네들 쓰면 시간이 좀 더 걸리는데, 입출력 수가 좀 많아서 그거 쌓여서 시간초과가 난 것. 그래서 대신에 scanf printf \n 이거 쓰니까 ㅈㄴ 잘 돌아감 씨빨 예전에 파이썬 쓸 때도 시간초과 나서 sys.stdin.readline() 이거 쓰게 됐던 것 같은데 비슷한 상황인듯
*/