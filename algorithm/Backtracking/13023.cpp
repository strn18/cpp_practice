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

/*
어렵지 않았던 백트래킹 문제. 어떠한 정점에서 시작하여, 깊이가 4(시작하는 노드 제외)까지 들어가는 노드를 찾을 수 있다면 1을, 없다면 0을 출력한다.
이걸 구하기 위해, start 노드에서 시작하여 깊이 n인 노드가 있다면 true를 반환하는 search 함수를 만들었다. 그 다음, 메인 함수에서 모든 노드에 대해
search 함수를 쳐주고(이때 n값은 4로 준다), true라면 1을 출력하고 바로 종료. 모든 노드에서 못 찾으면 0을 출력.

search 함수는, 우선 기저 조건으로 n이 0이면 끝에 온 것이니까 true를 반환한다. 그렇지 않으면 우선 start 노드 방문 체크하고, start의 인접 노드들 중
방문하지 않은 노드들에 대해 search를 재귀로 쳐준다(이때 n은 1 감소시켜서 줌). 만약 true인 경우가 있다면, start 노드에서 시작해서 깊이가 n까지
들어가는 노드를 찾은 것이니까 바로 true 리턴. 끝까지 못 찾으면, 방문 체크 해제하고 false를 리턴한다.

맞고 나서, visited에 memset 해주는 부분은 필요 없을 것 같아서(만약 24행에서 false가 리턴되면, 모든 search 함수가 false 값을 리턴한 거니까, 
visited 값은 알아서 false가 된다. 만약 true가 리턴되면 바로 1 출력하고 종료하니깐 상관 없음. 그래서 필요 없다고 생각해서 visited를 선언할 때
바로 false로 초기화 해줌) 지웠는데 시간이 오히려 좀 더 늘어남. 왜지??
*/