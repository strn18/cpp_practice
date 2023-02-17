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

/*
어렵지 않았던 플로이드 문제. 정점과 간선(단방향)이 주어졌을 때, 길이가 가장 짧은 사이클을 찾으면 된다.
이를 위해 우선 dist[i][j]: i에서 j로 가는 최단거리. 를 잡고, 플로이드를 쳐서 채웠다. 그런 다음, i에서 시작하는 가장 짧은 사이클을
찾으려면, dist[i][j]+dist[j][i] 중 최솟값을 찾아주면 된다(단, i!=j이고, 두 dist가 INF가 아니어야 함). 즉 i와 j가 1~V 일 때,
dist[i][j]+dist[j][i]의 최솟값을 찾으면 된다. 

풀어서 맞고 나서 https://www.acmicpc.net/source/55974184 이 풀이를 봤는데 괜찮아보였다. 나는 dist를 초기화할 때 i==j이면 0을 넣고,
아니라면 INF를 넣었는데, 이 풀이에서는 모두 INF를 넣는다. 그런 다음, 플로이드를 똑같이 치고, 최소 사이클을 구할 때 i가 1~V 일 때,
dist[i][i]의 최솟값을 찾는 방식이었다. 이게 가능한 이유는, 초기에 모든 dist[i][i]에 INF를 넣었으니, dist[i][i]는 dist[i][j]+dist[j][i]
의 최솟값이 들어가게 된다(i에서 i로 바로 가는 경로가 없으므로, i에서 j로 갔다가 j에서 i로 오는 최소 경로가 들어간다. 없으면 INF 그대로임).
그렇기 때문에 dist[i][i]는 결국 i에서 시작하는 최소 사이클 값이 되는 것. 그렇기에 dist[i][i]의 최솟값을 찾아주면 된다.
*/