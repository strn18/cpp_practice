#include <iostream>
#include <vector>
#include <queue>
#define INF 99999999
#define MAX 1000

using namespace std;

int N, M, X;
int dist[MAX+1][MAX+1]; // dist[i][j]: i에서 j로 가는 최소 시간
vector<pair<int, int>> time[MAX+1]; // time[i]: i에서 출발하는 도로. (-소요 시간, 도착 마을)

void dijkstra(int start);

int main(){
  int longest = -1;

  scanf("%d %d %d", &N, &M, &X);

  for(int i=0; i<M; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    time[a].push_back({-c, b});
  }

  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      dist[i][j] = (i == j ? 0 : INF);

  for(int i=1; i<=N; i++)
    dijkstra(i);
  
  for(int i=1; i<=N; i++)
    longest = max(longest, dist[i][X]+dist[X][i]);
  
  printf("%d", longest);

  return 0;
}

void dijkstra(int start){
  priority_queue<pair<int, int>> pq;
  pq.push({0, start});

  while(!pq.empty()){
    int cur_time = -pq.top().first;
    int cur_num = pq.top().second;
    pq.pop();

    if(dist[start][cur_num] < cur_time) continue;
    
    for(int i=0; i<time[cur_num].size(); i++){
      int next_time = -time[cur_num][i].first;
      int next_num = time[cur_num][i].second;
      
      if(cur_time + next_time < dist[start][next_num]){
        dist[start][next_num] = cur_time + next_time;
        pq.push({-dist[start][next_num], next_num});
      }
    }
  }
}

/*
살짝 꼬아놓은 다익스트라 문제인데, 어렵지는 않았음. i는 [1~N]일 때, i번 마을에서 X번 마을로 가는 최소 시간 + X번 마을에서 다시 i번 마을로 돌아오는
최소 시간 의 값 중 가장 큰 값을 찾으면 된다. 그래서 나는, dist[i][j]: i번 마을에서 j번 마을로 가는 최소 시간. 으로 정의하고, i가 [1, N]을 돌게
해서 각 마을에서 다른 마을로 가는 최소 시간을 모두 찾았다. 그 다음, dist[i][X] + dist[X][i]의 최댓값을 찾아서 출력하였다.
쉽게 풀렸지만, 코드 시간이 오래 걸렸다. 아무래도, ElogV 의 다익스트라를 V번 하게 되어, 시간초과는 안 났지만 시간이 오래 걸린듯. 
*/