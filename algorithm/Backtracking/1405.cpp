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

/*
별로 안 어려웠는데 다 풀어놓고 뜬금 없는 데서 막힌 백트래킹 + dfs 문제.

문제 설명은 이리저리 복잡하지만, 잘 읽어보면 별 거 없다. 로봇이 동서남북으로 총 N번 이동을 하는데, 한 번 위치했던 칸을 다시 가지 않도록 이동해야
한다. 그거에 맞게 이동하는 경로를 다 dfs로 찾아보되, 로봇이 동서남북으로 이동하는 확률을 통해, 각 경로로 가게 될 확률을 다 더해서 출력하면 된다.

이를 위해 dfs 함수를 정의했는데, 로봇이 지금까지의 경로로 올 확률이 cur_count이고, 총 n번 움직였을 때, (r, c)로 가는 것이다. 35행에서 동서남북을
다 돌아보고, 각 방향으로 갈 확률이 0보다 크고, 각 방향의 칸을 아직 방문 안 했을 때, dfs를 쳐준다. 다 끝나면, 이번 칸 방문 체크를 해제하고 
백트래킹 해준다. 이때 각 위치에 대한 로봇의 방문 유무를 체크하기 위해 visited 배열을 만들었는데, 로봇은 총 14칸 이동할 수 있어서 넉넉히 50*50으로
만들고, 로봇의 초기 위치는 가운데(25, 25)로 했다. 그리고 로봇이 동서남북 각 방향으로 갈 확률은 p 배열에 담았다.

유의할 점은, 난 평소에 dr dc 배열을 북남서동 으로(습관적으로) 했는데, 문제에서 동서남북 순서로 확률을 주기 때문에, 그거랑 맞춰줘야한다(p 배열의
방향 순서랑 dr dc 배열 방향 순서를 맞춰야함). 이거 때문에 좀 틀렸다(3번째 제출). 근데 4번째 제출도 틀려서, 왜지? 하고 알바 끝나고 집 와서 
고민해보니, printf 함수의 반올림 문제였음. 따로 명시를 안 해주면 소수점 6자리까지 반올림을 해버려서, 문제에서 허용하는 오차를 벗어난다.
그래서 12자리까지 표현하도록 하니까 맞았다.
사실 첨에는 부동소수점 오차때문에 그러나? double로도 안 되면 long double을 해야하나? 싶었는데, 그 문제는 아니었다.
https://boycoding.tistory.com/152 여기 보니까 float 값의 정밀도는 6~9자리 이고, double 값의 정밀도는 15~18자리라고 한다. 즉 double을 쓰면
문제의 오차 조건은 안 벗어난다는 것.
*/