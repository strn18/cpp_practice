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

/*
분명 막 어려운 문제는 아닌데 ㅈ같았던 문제.. 

우선 처음에는 좀 잘못 생각했다. 나라들의 연합(국경이 열린)이 여러 개가 있을 수 있는데, 국경이 열린 나라는 모두 하나로 연결되는 줄 알고 이상하게
접근했었다. 그래서 그 이후에도 dfs나 이런 저런 쓰잘데기 없는 풀이 떠올리다가 결국 그룹이 몇 개인지 찾는 bfs 문제랑 거의 유사하다는 걸 알았고, 
bfs 방식으로 풀었다.

두 노드의 인구 차이가 L이상 R이하라면 연결된다고 보고, 노드들을 그룹 1, 그룹 2, ... 이렇게 배정한다. 그 다음, 각 그룹 별 인구 수의 총합인
group_po와 나라 수의 총합인 group_co를 노드를 그 그룹에 배정할 때마다 갱신해서, 모든 노드의 그룹 배정이 다 끝나면 각 노드 별로 평균 인구 수인
group_po[i]/group_co[i] 이걸 넣어줘서 인구 수를 갱신해준다. 인구 이동이 일어났는지 안 일어났는지는, groups 변수를 이용하여 구한다. groups 변수는
총 그룹이 몇 개인지 세는데, 이게 N*N과 같다면? 모든 노드가 각자 다른 그룹에 있다는 것이고, 모든 노드가 연결이 안 된다는 소리니까 인구 이동이 안
일어났다고 볼 수 있다. 그때 break한다.

일반 bfs 문제에다가 그룹 인구 수와 그룹 나라 수도 따져줘야해서 좀 복잡해지긴 했지만 그리 어렵지 않게 코드를 짜긴 했음. 근데 틀렸다고 떴다. 
왜 그런가 한참 고민했는데, 그룹의 최대 개수인 MAX_G를 잘못 설정했다. 노드가 최대 2500개이고, 그룹 번호는 1번부터 시작하니까 2500 초과로만
설정해주면 되는데, 1260으로 설정했었음. 이걸 왜 그랬냐면, bfs로 잘 풀기 전에는 어떤 노드가 주변 노드와 연결이 안 된다면 그룹에 배정을 아예 안
시켰었다. 즉 group[i][j] 이 값을 그냥 -1로 했던가 그랬음. 그래서, 그룹은 최소 2개의 노드로 이루어졌기에, 그룹의 최대 개수는 2500/2 = 1250개여서
1300정도로 설정하고 풀었었는데 그걸 그대로 가져와버림.. 씨발!!

그거 고치고 제출하니 맞았다. 근데 시간이 좀 오래 걸려서, 시간 짧게 걸린 다른 풀이들 보니까 group_po나 group_co에 해당하는 것들을 나처럼 배열로
안 쓰고 그냥 벡터로 썼더라. 그렇게 하니까 내 코드의 30~33행처럼 매 턴마다 0으로 초기화를 해줄 필요가 없어서 더 짧게 걸린듯?
*/