#include <iostream>
#define MAX 50

using namespace std;

bool visited[MAX][MAX] = {false};
int N;
int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0};
double count = 0.0;
double p[4];

void dfs(int r, int c, double cur_count, int n);

int main(){
  scanf("%d", &N);
  for(int i=0; i<4; i++){
    scanf("%lf", &p[i]);
    p[i] /= 100;
  }
    
  dfs(25, 25, 1.0, 0);
    
  printf("%.12f", count);
    
  return 0;
}

void dfs(int r, int c, double cur_count, int n){
  if(n == N) count += cur_count;
    
  else{
    visited[r][c] = true;

    for(int i=0; i<4; i++)
      if(p[i] && !visited[r+dr[i]][c+dc[i]])
        dfs(r+dr[i], c+dc[i], cur_count*p[i], n+1);
        
    visited[r][c] = false;
  }
}