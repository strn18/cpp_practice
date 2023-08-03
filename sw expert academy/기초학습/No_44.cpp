// [Pro] 물류허브(13. Dijkstra)
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, vector<pair<int, int>>> edge[2];
// edge[0][i]: 노드 i에서 시작하는 간선들을 벡터에 저장. 형태는 {-비용, 도착지}. 
// edge[1][i]: 간선 방향을 반대로 하여 저장.

int init(int N, int sCity[], int eCity[], int mCost[]) {
  edge[0] = unordered_map<int, vector<pair<int, int>>>();
  edge[1] = unordered_map<int, vector<pair<int, int>>>();

  for(int i=0; i<N; i++){
    int s = sCity[i], e = eCity[i], c = mCost[i];

    if(edge[0].find(s) == edge[0].end()) edge[0][s] = vector<pair<int, int>>();
    if(edge[1].find(e) == edge[1].end()) edge[1][e] = vector<pair<int, int>>();

    edge[0][s].push_back({-c, e});
    edge[1][e].push_back({-c, s});
  }

	return edge[0].size();
}

void add(int sCity, int eCity, int mCost) {
  if(edge[0].find(sCity) == edge[0].end()) edge[0][sCity] = vector<pair<int, int>>();
  if(edge[1].find(eCity) == edge[1].end()) edge[1][eCity] = vector<pair<int, int>>();

  edge[0][sCity].push_back({-mCost, eCity});
  edge[1][eCity].push_back({-mCost, sCity});
}

int dijkstra(int start, int rev){ // start에서 시작하여 다른 노드들로의 최소 비용의 합을 리턴. rev가 1이면 반대 방향 간선(edge[1])으로.
  int count = 0;
  priority_queue<pair<int, int>> pq; // {-비용, 도착지};
  unordered_set<int> visited;
  
  pq.push({0, start});

  while(!pq.empty()){
    int cur_cost = -pq.top().first;
    int cur_num = pq.top().second;

    pq.pop();

    if(visited.find(cur_num) != visited.end()) continue;

    visited.insert(cur_num);
    count += cur_cost;

    for(int i=0; i<edge[rev][cur_num].size(); i++){
      int next_cost = -edge[rev][cur_num][i].first;
      int next_num = edge[rev][cur_num][i].second;

      if(visited.find(next_num) != visited.end()) continue;

      pq.push({-(cur_cost + next_cost), next_num});
    }
  }

  return count;
}

int cost(int mHub) {
	return dijkstra(mHub, 0) + dijkstra(mHub, 1);
}

/*
백준 1238번 문제랑 매우 유사한 문제. 어떠한 노드 i가 있고, 1) i에서 다른 마을로 가는 최소 거리의 합, 2) 다른 마을에서 i로 가는 최소 거리의 합
이 두 개를 모두 구해야 한다. 이때, 단순히 생각한다면 1)을 구하기 위해서 다익스트라를 한 번, 그리고 2)를 구하기 위해서 다익스트라를 n(노드의 
개수)번 사용하게 된다. 근데, 그러면 너무 비효율적이다. 그렇기 때문에 생각을 약간 꼬아서, 2)를 구할 때 원래의 간선들을 사용하는 것이 아니라, 
간선의 방향을 반대로 한 간선들을 다익스트라로 사용하면, 다익스트라 한 번만에 구할 수 있다. 자세한 건 1238번 코드 참조.

이 문제도 마찬가지로, edge[0]에는 간선들을 원래 방향으로 담았고, edge[1]에는 방향을 반대로 바꾸어서(원래 {start, end, cost}라면 
{end, start, cost}로 바꿔서) 넣었다. 그런 다음, 함수 dijkstra에서, 인자 rev로 0을 주면 edge[0]을, 1을 주면 edge[1]을 사용하도록 했다. 
첫번째 풀이에서는 그냥 rev_dijkstra라고 함수를 따로 만들고, edge도 지금처럼 배열로 나눈 게 아니라 
unordered_map<int, vector<pair<int, int>>> edge;
unordered_map<int, vector<pair<int, int>>> rev_edge;
이렇게 두 개 만들었었는데, 너무 길어서 그냥 합쳤음.

따로 특별한 건 없지만, 이 edge를 만들 때 좀 고민을 했다. 왜냐? 마을의 최대 개수는 고작 600개밖에 되지 않지만, 마을의 번호가 1부터 
10억까지 가능해서, 배열을 사용하는 일반적인 방법은 쓸 수가 없음. 즉, vector<pair<int, int>> edge[MAX]; 이렇게 할 수가 없다는 것.

그래서 어떡할까 고민하다가, 그동안 배웠던 map을 쓰기로 했다. 가능한 줄은 몰랐는데, map의 {key, value}에서 value에 벡터도 넣을 수 있었다. 
그래서 value에 vector<pair<int, int>>를 담고, key는 마을의 번호로 사용하였다. 그런 다음, i번 마을의 간선들이 담긴 벡터를 사용하려면? 
edge[0][i](원래 방향) or edge[0][i](반대로 바꾼 방향)을 사용하면 된다. 

이때 유의할 점으로는, init 함수에서 edge[0]과 edge[1]을 비워줬다. 그리고 map에 대해서 어떠한 key값이 처음이라면, 빈 벡터를 넣어주기 위해 
19행과 20행처럼 했음. 30행과 31행도 마찬가지. 그리고 끝으로, 26행에서 마을의 개수를 return해주는 걸 빼먹었었음. 어떻게 할까 하다가, map의 
메소드를 찾아보니깐 요소의 개수를 리턴하는 size를 사용할 수 있길래 그걸 사용했다. 
*/