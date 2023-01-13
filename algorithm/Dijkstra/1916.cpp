#include <iostream>
#include <vector>
#include <queue>
#define INF 2100000000
#define MAX 1000

using namespace std;

int main(){
  int N, M, start, end;
  int min_cost[MAX+1]; // min_cost[i]: start에서 i까지 드는 최소 비용
  bool visited[MAX+1] = {false}; // min_cost[i]가 갱신되었다면 visited[i] = true
  vector<pair<int, int>> bus[MAX+1]; // bus[i]: (-비용, 도착지)

  scanf("%d", &N);
  scanf("%d", &M);

  for(int i=0; i<M; i++){
    int from, to, cost;
    scanf("%d %d %d", &from, &to, &cost);
    bus[from].push_back({-cost, to});
  }

  scanf("%d %d", &start, &end);

  for(int i=1; i<=N; i++)
    min_cost[i] = INF;
  min_cost[start] = 0;

  // dijkstra
  priority_queue<pair<int, int>> pq;
  pq.push({-min_cost[start], start});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_num = pq.top().second;
    pq.pop();
    
    if(visited[cur_num]) continue;
    visited[cur_num] = true;

    for(int i=0; i<bus[cur_num].size(); i++){
      int next_cost = -bus[cur_num][i].first;
      int next_num = bus[cur_num][i].second;

      if(cur_cost + next_cost < min_cost[next_num]){
        min_cost[next_num] = cur_cost + next_cost;
        pq.push({-min_cost[next_num], next_num});
      }
    }
  }

  printf("%d", min_cost[end]);

  return 0;
}

/*
쉬운 다익스트라 문제였지만, 개뜬금없이 시간초과나서 좀 배운 점이 있었던 문제.
그냥 기본적인 다익스트라 문제라서, 평소대로 pq 쓰면서 풀었다(첫번째 제출). 근데 시간초과가 났음. 아니 배열 안 쓰고 pq를 쓰면 시간이 줄면 줄었지
왜 시간초과가 나지? 싶어서 이것저것 찾아봤는데, 그러다가 그동안 pq로 풀던 방식의 문제점(배열 쓸 때에 비해서 생기는 문제점)을 발견했음.

그동안은, 어떠한 노드의 dist(여기선 min_cost)가 갱신되면, pq에 집어넣고, 35행에서 다시 while문으로 돌아오면, 비용이 최소인 노드를 찾아서 거길
기준으로 그 인접 노드의 dist를 갱신하는 과정을 반복한다. 근데 이렇게 하면, 어떠한 노드의 dist값이 두 번 갱신되었다면, pq에 (dist, 그 노드 번호)가
두 번 들어가게되면서, 그 노드에 대해 42행의 for문을 또 여러 번 실행하게 되면서 필요없는 연산을 반복하게 됨. 만약 어떠한 노드의 dist값이 두 번이
아니라 더 많이 갱신되었으면, 불필요한 연산이 쌓이겠지?
뭔 소리냐면, 1~3번 노드가 있고, 1번과 2번 사이가 4, 1번과 3번 사이가 1, 2번과 3번 사이가 2일 때, 맨 처음 1번 노드가 pq에 들어가고, 1번 노드를
대상으로 2번과 3번 노드의 dist를 각각 4, 1로 갱신하여 둘 다 pq에 넣어준다. 그 다음에는, pq에서 (1, 3)을 꺼내오고(비용이 1로 3번 노드가 
갱신되었으니까. 원래라면 pq를 최소 힙으로 쓰기 위해 -비용 이었겠지만 그건 생략), 3번 노드를 대상으로 다시 2번 노드의 dist가 1+2 = 3으로 갱신되어,
pq에 넣어준다. 이렇게 되면 pq에는 (비용, 노드 번호)의 형태로, (4, 2)와 (3, 2)가 둘 다 들어있다. 근데 여기서 (3, 2)만 필요한데(비용이 더 적으니깐,
(4, 2)는 어차피 갱신 안 될거라 필요 x), 불필요하게 (4, 2)까지 들어있어서 42행을 쓸데없이 반복하게 된다. 이게 쌓여서 시간초과가 나게 된 것임.

이걸 해결하기 위해, visited 배열을 썼다. 어떠한 노드의 dist값이 이미 최솟값으로 갱신되었다면, 42행을 돌지 않도록 그 위에서 검사해준다. 이렇게
해서 코드 고치고 제출하니까 맞았다.

만약 pq를 안 쓰고 배열을 쓰는 풀이였다면? min()을 쓰는 과정에서 시간이야 당연히 오래 걸리겠지만, 어쨌든 이 부분 관련해서는 불필요한 연산이
없었을 거임(min(dist)를 통해서, 노드가 N개 있다면 갱신을 N번만 하니까). 그동안 다익스트라 시간복잡도가 왜 O(N^2)이랑 O(NlogN)인지 잘 이해가
안 갔었는데, 이번에 풀면서 알게 되었음. 배열 쓰는 풀이는, min(dist)로 dist값이 제일 작은 노드를 찾아, 그걸 대상으로 갱신해주는 과정을 총 N번
(노드가 N개니까) 반복하게 되는데, 한 번 할 때마다 그 안에서 O(N)이니까(min() 쓰는 과정이 O(N)), O(N^2)이다.
pq 쓰는 풀이는, 똑같이 노드 N개에 대해서, 각 노드를 기준으로 갱신하는 과정을 N번 하게되고, 그 안에서 O(logN)이니까(pq.pop이나 pq.push는 
logN), 총 O(NlogN)이다.

https://yabmoons.tistory.com/364 
*/