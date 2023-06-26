#include <iostream>
#include <queue>
#include <cmath>
#define MAX 1000

using namespace std;

typedef struct{int x, y;} pos;

bool visited[MAX+1] = {false};
bool connected[MAX+1][MAX+1] = {false};

double dist(pos a, pos b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, count = 0;
  double ans = 0;
  priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
  pos coord[MAX+1];

  cin >> N >> M;
  
  for(int i=1; i<=N; i++)
    cin >> coord[i].x >> coord[i].y;
  
  for(int i=0; i<M; i++){
    int a, b;

    cin >> a >> b;

    connected[a][b] = true;
    connected[b][a] = true;
  }

  pq.push({0, 1});

  while(count < N){
    double d = pq.top().first;
    int cur = pq.top().second;

    pq.pop();

    if(visited[cur]) continue;

    visited[cur] = true;
    ans += d;
    count++;

    for(int i=1; i<=N; i++){
      if(visited[i]) continue;

      if(connected[cur][i]) pq.push({0, i});
      else pq.push({dist(coord[cur], coord[i]), i});
    }
  }

  cout << fixed;
  cout.precision(2);
  cout << ans;

  return 0;
}

double dist(pos a, pos b){
  return sqrt(pow((a.x-b.x), 2) + pow((a.y-b.y), 2));
}

/*
약간 응용된 MST 문제. 프림 알고리즘으로 풀었다.

N명의 우주신들을 모두 연결하면 되고, 이때 우주신들 사이의 간선의 길이는 둘 중 하나다.
1) 그냥 두 우주신의 좌표값으로 거리 계산. 2) 입력 M개의 줄에서 둘 사이의 연결된 통로가 주어졌을 경우, 거리는 0.
이걸 이용해서 pq에 잘 집어넣으면서 풀면 됨.

29행에서, 둘이 연결되었는지를 나타내는 2차원 배열인 connected를 사용했다. connected[a][b]가 true일 경우 둘 사이에 연결된 통로가 있는 것임.
38행에서, 1번째 우주신부터 시작한다.
40행에서 count는 그룹화가 완료된 우주신의 개수이므로, 이게 N이 되면 다 연결된 거니까 while문을 나가게 된다.
52행에서, 이제 cur번 우주신을 그룹화 완료했으니까, 걔로부터 다른 우주신으로 갈 수 있는 경로를 구해서 pq에 새로 넣어줘야 한다. 1~N번 우주신으로의
경로를 다 계산해보는데, 만약 i번 우주신이 이미 그룹화 완료라면 볼 필요 없다(53행). 그렇지 않고, cur와 i가 둘이 connected 되어 있다면 거리를 0으로
하는 경로를 pq에 넣어준다(55행). 그렇지 않다면 그냥 두 좌표 사이의 거리를 dist 함수로 계산하여 그 경로를 pq에 넣어준다(56행).

첫번째 제출에서 틀렸는데, 68행에서 pow((a.x-b.x), 2)가 아니라 (a.x-b.x)*(a.x-b.x) 로 해서, int형이니깐 제곱하니 오버플로우가 나서 틀렸다.
두번째 제출에서도 틀렸는데, 35행에서 connected[b][a] = true; 이걸 안 해줘서 틀렸음. 그거 고치니까 맞았다.
*/