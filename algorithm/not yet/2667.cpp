/*
#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>

#define MAX 25

using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int house[MAX][MAX] = {0}; // 집이 없으면 0, 있는데 단지 계산 전이면 1, N단지에 속하면 N
int nums_of_house[MAX*MAX] = {0}; // 인덱스 단지의 수

int N;
int complex = 0; // complex개의 단지 발견

void bfs(int r, int c, int idx); // (r, c)를 시작으로 idx단지 찾기 시작(idx는 2부터 시작함)

int main(){
  scanf("%d", &N);

  getchar();
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      char temp;
      scanf("%c", &temp);
      house[i][j] = temp-'0';
    }
    getchar();
  }
  
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      if(house[i][j]==1)
        bfs(i, j, complex+2);
  
  printf("%d\n", complex);
  if(complex==0){
    printf("0");
    return 0;
  }

  sort(nums_of_house+2, nums_of_house+2+complex);
  
  for(int i=2; i<complex+2; i++)
    printf("%d\n", nums_of_house[i]);

  return 0;
}

void bfs(int r, int c, int idx){
  queue<pair<int, int>> q;
  q.push(make_pair(r, c));
  //q.push({r, c});
  house[r][c] = idx; // 여기는 이제 idx단지
  nums_of_house[idx]++; // idx단지 수 증가

  while(!q.empty()){
    pair<int, int> p = q.front();
    q.pop();

    for(int i=0; i<4; i++){ // 상하좌우가 범위 내이고 house가 1이라면 단지에 포함
      int rpos = p.first+dr[i];
      int cpos = p.second+dc[i];
      if(0<=rpos && rpos<N && 0<=cpos && cpos<N && house[rpos][cpos]==1){
        q.push(make_pair(rpos, cpos));
        house[rpos][cpos] = idx;
        nums_of_house[idx]++;
      }
    }
  }
  
  complex++;
}

bfs나 dfs로 순회하는 문제라는데 bfs로 푼 문제. 이거 풀 때 머리가 뭔가 멍한 상태라 좀 버벅이긴 했는데 사실 별로 어려운 건 없었음. 그냥 인접리스트 대신에 상하좌우 탐색하면 되는거고, house 배열에 집이 없으면 0, 있는데 단지 포함 안 됐으면 1, n단지에 포함됐으면 n을 넣은 후 탐색할 때 상하좌우 house 값이 1이면 현재 탐색 중인 단지에 포함시키고 house 값 바꾸는 식으로 bfs 쓰면 되는 거라 간단했다. 다만 두 가지 유의점이 있었는데 하나는 0이나 1 입력받을 때 숫자가 붙어서 입력되는지라 그냥 scanf("%d") 반복문으로 받으면 안 되길래 우선 scanf("%c")로 임시 char 변수에 넣은 후 그 값 조작해서 다시 넣어주는 방식으로 했다. 두 번째는 각 단지 내 집의 수를 오름차순으로 출력해야해서 sort해주는 건데, 이거는 문제 풀 때 인지하고 있던 건데 잠시 까먹었다.

딴 사람들 풀이 보니까 dfs로 푼 것도 있던데 그 부분은 사실상 차이 없었다. 그거 말고 다른 점으로는, 나는 house 배열에 입력도 받고 거기에 몇 단지인지도 표기하는 식으로 했고 단지 당 집의 수를 nums_of_house 배열에 기록해두는 식으로 했는데, 딴 사람들은 입력받는 배열은 string 형으로 하고 새로 visited 배열을 선언해서 방문했으면 1을 넣는 식의 풀이가 많았다. 또한 단지 당 집의 수는 단지 계산 끝날 때마다 벡터에 push하는 방식이었음. 이게 더 좋은듯. 
그리고 make_pair(r, c) 이거 대신에 {r, c} 이렇게 해도 된다고 한다. (57행)
그거 말고도 다른 활용법들(tuple, tie, auto 등등) 정리되어있는 링크
https://runa-nam.tistory.com/72
*/