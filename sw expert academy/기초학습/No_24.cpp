// [S/W 문제해결 응용] 4일차 - 보급로(7. Heap)
#include <iostream>
#include <queue>
#include <string>
#define MAX 100
#define INF 2100000000

using namespace std;

int N;

int board[MAX][MAX];
int dist[MAX][MAX];

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool out_of_bound(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    cin >> N;

    for(int i=0; i<N; i++){
      string str;

      cin >> str;

      for(int j=0; j<N; j++){
        board[i][j] = str[j] - '0';
        dist[i][j] = INF;
      }
    }

    priority_queue<pair<int, pair<int, int>>> pq;

    pq.push({-board[0][0], {0, 0}});

    while(!pq.empty()){
      int cur_cost = -pq.top().first;
      int cur_r = pq.top().second.first;
      int cur_c = pq.top().second.second;

      pq.pop();

      if(cur_cost >= dist[cur_r][cur_c]) continue;

      dist[cur_r][cur_c] = cur_cost;

      for(int i=0; i<4; i++){
        int next_r = cur_r + dr[i];
        int next_c = cur_c + dc[i];

        if(out_of_bound(next_r, next_c)) continue;

        int next_cost = board[next_r][next_c];

        if(cur_cost + next_cost < dist[next_r][next_c]) pq.push({-(cur_cost + next_cost), {next_r, next_c}});
      }
    }

    cout << '#' << t << ' ' << dist[N-1][N-1] << '\n';
  }

  return 0;
}

bool out_of_bound(int r, int c){
  if(r<0 || N<=r || c<0 || N<=c) return true;
  else return false;
}

/*
쫌 까다롭다고 생각했는데 별 거 없었던 문제.

처음에는 dp로 접근하려 했다. dp[i][j] = (i, j)까지 오는 데 드는 비용(그 칸 복구 비용 포함). 으로 정의하고, 
dp[i][j] = min(dp[상하좌우] + board[i]][j]) 뭐 이런 식으로 잡았었다. 근데 그렇게 했더니, 어떤 칸의 dp 값을 채우려면 그 오른쪽 칸의 dp 값을 
채워야 하는데, 그걸 채우려면 또 그 왼쪽 칸의 dp 값을 채워야 하고, ... 이런 식으로 무한반복 데드락이 걸려버리는 문제가 생김.

그래서 이건 아닌 것 같고 어떡하지? 하다가 그냥 누가봐도 시간초과 날 것 같지만 dfs로 짜보기로 함. 그래서 짰더니 당연히 N이 커지니까 시간초과.

그래서 고민 많이 하다가 https://chanhuiseok.github.io/posts/algo-32/ 여기를 깔짝 봤었는데, 큐를 쓴다는 거 보고 아 이거 그냥 pq로 
다익스트라 치면 되는 거 아닌가? 싶어서 그렇게 풀어봤다(블로그 풀이는 좀 다르지만(bfs), 그거보다 다익스트라가 효율적인 것 같아서 다익스트라로 함).

그래서 그냥 매우 전형적인 다익스트라 문제로 풀었더니 맞았다. 상하좌우 칸에 간선이 있다고 생각하고 다익스트라 쳐주면 됨.
*/