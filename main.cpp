#include <iostream>
#include <queue>
#define MAX_N 50
#define MAX_G 2510

using namespace std;

int N, L, R;
int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
int po[MAX_N][MAX_N], group[MAX_N][MAX_N];
int group_po[MAX_G], group_co[MAX_G];
int groups = 0;

void bfs(int r, int c, int n);
int absolute(int a, int b);

int main(){
  int days = 0;

  scanf("%d %d %d", &N, &L, &R);
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &po[i][j]);

  while(true){
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
        group[i][j] = 0;

    for(int i=1; i<=groups; i++){
      group_po[i] = 0;
      group_co[i] = 0;
    }

    groups = 0;

    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
        if(group[i][j] == 0)
          bfs(i, j, ++groups);
    
    if(groups == N*N) break;

    days++;

    for(int i=1; i<=groups; i++)
      group_po[i] /= group_co[i];

    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
        po[i][j] = group_po[group[i][j]];
  }

  printf("%d", days);

  return 0;
}

void bfs(int r, int c, int n){
  queue<pair<int, int>> q;
  group[r][c] = n;
  group_po[n] += po[r][c];
  group_co[n]++;
  q.push({r, c});

  while(!q.empty()){
    int cur_r = q.front().first;
    int cur_c = q.front().second;
    q.pop();

    for(int i=0; i<4; i++){
      int nr = cur_r+dr[i];
      int nc = cur_c+dc[i];

      if(nr<0 || N<=nr || nc<0 || N<=nc || group[nr][nc]!=0) continue;

      int diff = absolute(po[cur_r][cur_c], po[nr][nc]);
      if(L<=diff && diff<=R){
        group[nr][nc] = n;
        group_po[n] += po[nr][nc];
        group_co[n]++;
        q.push({nr, nc});
      }
    }
  }
}

int absolute(int a, int b){
  return (a-b>=0 ? a-b : b-a);
}