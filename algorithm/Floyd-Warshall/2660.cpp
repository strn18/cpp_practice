#include <iostream>
#include <vector>
#define MAX 50
#define INF 1000000000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  int dist[MAX+1][MAX+1];

  int minPoint = MAX;
  int point[MAX+1] = {0};
  vector<int> candidate;

  cin >> N;

  // initialization
  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      dist[i][j] = (i == j ? 0 : INF);
  
  // input
  while(true){
    int a, b;

    cin >> a >> b;

    if(a == -1) break;

    dist[a][b] = 1;
    dist[b][a] = 1;
  }

  // floyd-warshall
  for(int k=1; k<=N; k++)
    for(int i=1; i<=N; i++)
      for(int j=1; j<=N; j++)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  // calculate point
  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      point[i] = max(point[i], dist[i][j]);
  
  // find candidates and their points
  for(int i=1; i<=N; i++){
    if(point[i] <= minPoint){
      if(point[i] < minPoint) candidate.clear();

      minPoint = min(minPoint, point[i]);
      candidate.push_back(i);
    }
  }

  // print answer
  cout << minPoint << ' ' << candidate.size() << '\n';
  for(auto e: candidate)
    cout << e << ' ';

  return 0;
}

/*
그냥 플로이드 와샬 쓰면 되는 문젠데, 24행에서 dist[i][i]는 간선 비용 0으로 해놨어야 하는데 안 해서 첫 제출 때 틀렸다. 
*/