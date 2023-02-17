#include <iostream>
#define MAX 400
#define INF 2100000000

using namespace std;

int dist[MAX+1][MAX+1];

int main(){
  int V, E, min_cycle;

  scanf("%d %d", &V, &E);

  for(int i=1; i<=V; i++)
    for(int j=1; j<=V; j++)
      dist[i][j] = INF;

  for(int i=0; i<E; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    dist[a][b] = c;
  }

  for(int k=1; k<=V; k++){
    for(int i=1; i<=V; i++){
      if(dist[i][k] == INF) continue;
      for(int j=1; j<=V; j++){
        if(dist[k][j] == INF) continue;
        dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
      }
    }
  }

  min_cycle = INF;
  for(int i=1; i<=V; i++)
    min_cycle = min(min_cycle, dist[i][i]);

  printf("%d", (min_cycle==INF ? -1 : min_cycle));
  
  return 0;
}