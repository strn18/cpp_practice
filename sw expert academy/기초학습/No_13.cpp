// 기초 DFS 연습(5. 그래프)
#define MAX 100

int adj[MAX][MAX]; // adj[i][j] = k: i왕의 j번째 자식은 k왕
int child[MAX]; // child[i] = j: i왕의 자식은 j명

void dfs_init(int N, int path[100][2])
{
  for(int i=1; i<MAX; i++)
    child[i] = 0;

  for(int i=0; i<N-1; i++){
    int a = path[i][0], b = path[i][1];
    adj[a][child[a]++] = b;
  }
}

int dfs(int n)
{
  int st[MAX];
  int top = -1;

  st[++top] = n;

  while(top != -1){
    int cur = st[top--];

    if(cur > n) return cur;

    for(int i=child[cur]-1; i>=0; i--)
      st[++top] = adj[cur][i];
  }

  return -1;
}

/*
걍 dfs 하면 되는 문젠데, <vector>를 못 써서 인접행렬+스택으로 풀었음. 스택도 배열로 직접 구현했다.
*/