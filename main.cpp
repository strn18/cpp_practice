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