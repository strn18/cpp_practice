#include <iostream>
#define MAX 200
#define INF 2100000000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  int dist[MAX+1][MAX+1];
  int ans[MAX+1][MAX+1];

  cin >> n >> m;

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      dist[i][j] = INF;

  for(int i=0; i<m; i++){
    int a, b, c;

    cin >> a >> b >> c;

    dist[a][b] = c;
    dist[b][a] = c;

    ans[a][b] = b;
    ans[b][a] = a;
  }

  for(int k=1; k<=n; k++){
    for(int i=1; i<=n; i++){
      if(dist[i][k] == INF) continue;

      for(int j=1; j<=n; j++){
        if(dist[k][j] == INF) continue;

        if(dist[i][k]+dist[k][j] < dist[i][j]){
          dist[i][j] = dist[i][k]+dist[k][j];
          ans[i][j] = ans[i][k];
        }
      }
    }
  }

  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      if(i==j) cout << '-';
      else cout << ans[i][j];
      cout << ' ';
    }
    cout << '\n';
  }

  return 0;
}

/*
다익스트라 찾아서 풀었는데 문제 읽어보니깐 플로이드 와샬이라 그거로 풀었던 문제.

일반적인 플로이드 문제랑 거의 똑같고, i에서 j로 최소비용으로 가는 경로가 있을 때, i에서 출발하여 처음으로 지나는 노드를 찾으면 된다. 즉, 
i -> a -> b -> j 가 최소비용 경로라면 a가 된다. 이를 위해, ans[i][j]: i에서 j로 최소 비용으로 갈 때 가장 먼저 들르는 곳. 이라고 정의하고
풀었다. 처음에 경로 입력받는 부분에서, (a b c)를 입력받았다면, a에서 b로 가는데 c 비용이 드는 것이니까, ans[a][b] = b로 우선 넣어줌(제일 먼저
들르는 곳이 b이므로). 그 다음은 그냥 플로이드 문제랑 거의 비슷하게 하면 되고, 42행에서 한 것처럼 최소비용 갱신해줄 때 ans도 같이 갱신해주면
된다. i에서 j로 갈 때, k를 들러서 가는 게 최소비용이라면? i에서 k로 갈 때 처음 들르는 곳이 ans[i][j]가 될 것임. 즉 ans[i][j] = ans[i][k]이다.
*/