/*
#include <iostream>
#include <queue>

using namespace std;

queue<int> S;
int s_cases[3];
int visited[100001] = {0};

int count = 0;

void bfs(int sister);

int main(){
  int subin, sister;
  scanf("%d %d", &subin, &sister);
  S.push(subin);
  
  if(sister<=subin)
    count = subin-sister;
  else
    bfs(sister);
  
  printf("%d", count);
  
  return 0;
}

void bfs(int sister){
  while(1){
    int n = S.size();
    count++;
    for(int i=0; i<n; i++){
      int cur = S.front();
      s_cases[0] = cur*2; s_cases[1] = cur+1; s_cases[2] = cur-1;
      S.pop();
      for(int j=0; j<3; j++){
        if(s_cases[j]==sister)
          return;
        if(0<=s_cases[j] && s_cases[j]<=100000 && visited[s_cases[j]]==0){
          S.push(s_cases[j]);
          visited[s_cases[j]] = 1;
        }
      }
    }
  }
}

처음에는 이게 왜 bfs 문제지 싶었는데, 수빈이가 n일차에 갈 수 있는 방법 3가지(*2, +1, -1)를 bfs처럼 탐색한다고 생각하니 bfs문제 맞았음. 그리고 이미 간 칸을 또 가는 경우(가령 2일차에 4를 이미 갔는데, 6일차에 또다시 4를 간다든가 하는건 애초에 가장 빠른 경우의 수가 아니므로 탐색할 필요 x)를 배제하기 위해 visited 배열을 만들었고, 수빈이가 갈 수 있는 3칸을 for문으로 돌리기위해 s_cases 배열을 만들어서 썼다. 이후 다른 과정은 그냥 bfs 문제와 별 차이 없었음. 다만 count++ 해주는 부분을 처음에는 37행과 38행 사이에 넣는 바람에 틀린 답이 나왔고, 이후 현재처럼 제대로 옮김.
*/