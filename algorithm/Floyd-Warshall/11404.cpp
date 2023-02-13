#include <iostream>
#define MAX 100
#define INF 1000000000

using namespace std;

int main(){
  int n, m;
  int dist[MAX+1][MAX+1];

  scanf("%d", &n);
  scanf("%d", &m);

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      dist[i][j] = INF;

  for(int i=1; i<=n; i++)
    dist[i][i] = 0;
  
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    dist[a][b] = min(dist[a][b], c);
  }
  
  for(int k=1; k<=n; k++)
    for(int i=1; i<=n; i++)
      for(int j=1; j<=n; j++)
        dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
  
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++)
      printf("%d ", dist[i][j] == INF ? 0 : dist[i][j]);
    printf("\n");
  }

  return 0;
}

/*
처음 풀어본 플로이드-와샬 문제. https://blog.naver.com/kks227/220797649276 여기를 많이 참고해서 풀었다. 
제출했더니 한 번 틀렸었는데, 30행에서 dist값 두 개 더한 값을 dist[i][j]와 비교하는 부분에서, 오버플로우가 난듯. 처음에는 INF를 21억으로 두고
풀어서 두 INF 값이 더해지니 오버플로우가 났다. 그래서 INF를 10억으로 바꿈. 그리고, 문제를 잘 읽어보면 i에서 j로 갈 수 없는 경우에는 0을
출력하라고 했는데, 그 부분을 체크해주지 않아서 또 틀렸다. 그래서 34행에서 INF값이면 0을 출력하는 걸로 바꿨더니 맞았음.

링크 밑에 댓글 읽어보면, dist[i][k]가 INF면(경로가 없으면) continue하는 방법도 있다고 한다. 그리고
https://melonicedlatte.com/algorithm/2018/07/09/011740.html 여기 글 읽어보면, dist[i][k]와 dist[k][j]가 둘 다 INF가 아닐 때만
30행의 점화식을 쳐주는 부분도 볼 수 있었음. 경로가 없으면 커팅하는 방법도 좋은 것 같다.
*/