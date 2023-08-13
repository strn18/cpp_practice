// 15965. [Pro] 항공노선관리
#include <vector>
#include <queue>
#define MAX 60
#define INF 2100000000

using namespace std;

int n;

// these are for minTravelTime();
typedef struct{
  int start_time, travel_time;
} edge_info;

vector<edge_info> edge[MAX][MAX];

typedef struct{
  int total, node, time;
} pq_info;

struct compare{
  bool operator()(pq_info a, pq_info b){
    return a.total > b.total;
  }
};

// this is for minPrice();
int cost[MAX][MAX]; // 최소 비용 저장. INF면 경로가 없다.

void init(int N)
{
  n = N;

  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      edge[i][j] = vector<edge_info>();

  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      cost[i][j] = INF;
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
  edge[mStartAirport][mEndAirport].push_back({mStartTime, mTravelTime});

  cost[mStartAirport][mEndAirport] = min(cost[mStartAirport][mEndAirport], mPrice);
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
  priority_queue<pq_info, vector<pq_info>, compare> pq;
  bool visited[MAX] = {false};

  pq.push({0, mStartAirport, mStartTime});

  while(!pq.empty()){
    pq_info cur = pq.top();

    pq.pop();

    if(cur.node == mEndAirport) return cur.total;

    if(visited[cur.node]) continue;

    visited[cur.node] = true;

    for(int i=0; i<n; i++){
      if(visited[i]) continue;

      for(int j=0; j<edge[cur.node][i].size(); j++){
        edge_info next = edge[cur.node][i][j];

        int wait_time = next.start_time - cur.time;

        if(wait_time < 0) wait_time += 24;

        pq.push({cur.total + wait_time + next.travel_time, i, (next.start_time + next.travel_time) % 24});
      }
    }
  }

	return -1;
}

int minPrice(int mStartAirport, int mEndAirport)
{
  int total_cost[MAX]; // total_cost[i]: mStartAirport에서 i로 가는 최소 비용.
  bool visited[MAX] = {false};

  for(int i=0; i<n; i++) total_cost[i] = INF;

  total_cost[mStartAirport] = 0;

  while(true){
    int min_node = -1, min_cost = INF;

    for(int i=0; i<n; i++){
      if(visited[i] || total_cost[i] == INF) continue;

      if(total_cost[i] < min_cost){
        min_node = i;
        min_cost = total_cost[i];
      }
    }

    if(min_node == -1) return -1;
    if(min_node == mEndAirport) return min_cost;
    
    visited[min_node] = true;

    for(int i=0; i<n; i++)
      if(cost[min_node][i] != INF)
        total_cost[i] = min(total_cost[i], min_cost + cost[min_node][i]);
  }

	return 0; // never happens
}

/*
이번엔 쫌 쉬운 문제였음. 그냥 적절히 다익스트라를 두 번 쳐주면 되는 문제다.

우선, minPrice 함수는 매우 쉽다. 그냥, 주어지는 간선 정보 중에서 티켓 가격(mPrice) 정보만 사용하면 됨. 노드의 최대 개수가 60개이므로, 
굳이 벡터를 사용하지 않고 2차원 배열을 사용하였다(29행의 cost). 그리고 add로 간선을 입력받는 과정에서, A->B로의 가격이 C인 간선인데, 
C < cost[A][B]라면 cost[A][B] = C로 갱신시키도록 하였다.

minPrice 함수에서는 역시 마찬가지로, pq를 사용하지 않고 그냥 O(V^2)의 다익스트라를 사용하였다. 우선 주어진 노드들 중, 1) 아직 방문하지 
않았고, 2) mStartAirport에서 해당 노드로의 cost(total_cost)가 최소인 노드를 찾는다(99~106행). 그런 다음, 방문 표시를 하고 걔에서 시작되는 
간선들을 돌면서, total_cost를 갱신시켜주면 된다.

그 다음, minTravelTime 함수는 약간 꼬아놨지만, 결국 pq를 사용하는 일반적인 다익스트라와 다를 바가 없다. 일반적인 다익스트라 문제를 풀 때는 
pq에 {현재까지의 코스트, 현재 노드 번호} 정보를 넣지만, 여기서는 추가적으로 현재 시각에 대한 정보도 넣어야 한다. 왜냐? 일반적인 다익스트라 
문제에서는, A 노드에서 B 노드로 C 코스트가 필요할 때, 그냥 딴 거 필요 없이 C 코스트만을 사용해서 A->B로 이동할 수 있다. 그러나, 이 문제에서는 
간선 정보에 비행 소요 시간(코스트) 뿐만 아니라 출발 시각도 주어진다. 그렇기에, 현재 시각과 출발 시각을 통해 기다리는 시간이 그 간선을 이동하는 
코스트에 추가되게 된다. 

때문에, 간선을 edge에 담았는데, edge는 2차원 배열 형태이고 벡터를 요소로 갖는다. 즉 edge[i][j]에는 i->j로의 간선들이 벡터에 담긴다.
그런 다음 72행 부분에서, 방금 도착한 노드에서 시작되는 간선들을 보면서 pq에 push를 해줘야 한다. 이때, wait_time을 계산해준다. 이는 출발 
시각에서 현재 시각을 뺀 값으로 구할 수 있는데, 그 값이 0 이상이면 그대로 쓰면 되고, 음수면 24를 더해줘야 한다. 
그런 다음, 현재까지의 코스트(cur.total)에 wait_time을 더하고 비행 소요 시간(next.travel_time)을 더해서 pq에 코스트로 넣어준다. 또한 
현재 시각도 넣어줘야 하는데, 이건 출발 시각(next.start_time)에 비행 소요 시간을 더해서 구할 수 있다. 이게 24 이상이면 안 되므로 나머지 연산도 
해야함. 

이런 식으로 해서, 현재까지의 코스트(total)를 기준으로 하는 최소힙으로 pq를 사용하면 된다.
*/