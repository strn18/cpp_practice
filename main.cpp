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