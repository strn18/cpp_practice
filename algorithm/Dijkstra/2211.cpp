#include <iostream>
#include <vector>
#include <queue>
#define MAX 1000
#define INF 2100000000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  int dist[MAX+1];
  vector<pair<int, int>> adj[MAX+1]; // {-거리, 도착 지점}
  priority_queue<pair<int, pair<int, int>>> pq; // {-거리, {중간 지점, 도착 지점}}

  int ans[MAX+1];

  cin >> N >> M;

  for(int i=1; i<=N; i++)
    dist[i] = INF;

  for(int i=0; i<M; i++){
    int A, B, C;

    cin >> A >> B >> C;

    adj[A].push_back({-C, B});
    adj[B].push_back({-C, A});
  }

  pq.push({0, {1, 1}});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int prev_num = pq.top().second.first;
    int cur_num = pq.top().second.second;

    pq.pop();

    if(dist[cur_num] != INF) continue;

    dist[cur_num] = cur_cost;
    ans[cur_num] = prev_num;

    for(int i=0; i<adj[cur_num].size(); i++){
      int next_cost = -adj[cur_num][i].first;
      int next_num = adj[cur_num][i].second;

      if(dist[next_num] != INF) continue;

      pq.push({-(cur_cost + next_cost), {cur_num, next_num}});
    }
  }

  cout << N-1 << '\n';

  for(int i=2; i<=N; i++)
    cout << ans[i] << ' ' << i << '\n';

  return 0;
}

/*
오랜만에 풀어본 다익스트라 문제.

1번 컴퓨터에서 시작해서 다른 컴퓨터들로 가는 최소 경로를 다익스트라로 구하는 데, 이때 어떤 간선이 최소 경로에 쓰였는지를 체크해주면 된다.
이를 위해, 원래 다익스트라에서는 pq를 {-거리, 도착지} 형태로 사용했는데 여기서는 {-거리, {경유지(지나는 중간 지점), 도착지}} 형태의 원소를
넣어주었다. 이를 이용해서, 이 간선이 최소 경로에 사용되었을 경우, {경유지, 도착지}를 잇는 간선이 쓰인 거니까 ans에 표시해주면 된다.

처음에는 ans를 pair<int, int> 형태의 벡터로 써서 {경유지, 도착지}를 다 넣어주고 나중에 다 출력했었는데,
https://yabmoons.tistory.com/444 여기 풀이를 보고 좀 바꿈. 어차피 출력하는 K개의 간선은 반드시 N-1개이다. 
참고로 ans의 첫번째 원소(여기서는 ans[1])는 출력하지 않는다. 얘는 그냥 처음에 35행에서 1번 노드를 pq에 넣어줄 때 쓴 거니까 실제 간선이 아님.
*/