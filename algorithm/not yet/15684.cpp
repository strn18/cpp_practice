/*
#include <iostream>
#include <algorithm>

using namespace std;

int N, M, H;
int hor[11][31] = {0};

void put(int used, int mx);
int check(void);

int main(){
  scanf("%d %d %d", &N, &M, &H);
  for(int i=0; i<M; i++){
    int a, b;
    scanf("%d %d", &a, &b);
    hor[b][a]=1;
  }

  for(int i=0; i<=3; i++)
    put(0, i);

  printf("-1");

  return 0;
}

void put(int used, int mx){
  if(used==mx){
    if(check()){
      printf("%d", used);
      exit(0);
    }
    return;
  }

  for(int i=1; i<N; i++){
    for(int j=1; j<=H; j++){
      if(!hor[i][j] && !hor[i-1][j] && !hor[i+1][j]){
        hor[i][j] = 1;
        put(used+1, mx);
        hor[i][j] = 0;

        while(!hor[i-1][j] && !hor[i+1][j]) j++;
      }
    }
  }
}

int check(void){
  for(int i=1; i<N; i++){
    int v = i;
    for(int j=1; j<=H; j++){
      if(hor[v-1][j]) v--;
      else if(hor[v][j]) v++;
    }
    if(i!=v)
      return 0;
  }
  return 1;
}

파이썬으로 푼 1062처럼 백트래킹인데, 분명 풀이는 대강 알겠는데 구현하려니까 너무 좃같았던 문제.. 우선 위 코드는 https://velog.io/@statco19/boj-15684 여기 코드를 참조한 코드인데, 도대체 45행이 뭔 의미인지도 모르겠고 왜 저거 하나 때문에 시간초과/0ms성공이 갈리는지도 몰겠음
그리고 https://artjjong.tistory.com/67 여기 코드랑 비슷한 코드로도 하나 써서 제출했는데 내 생각에는 그게 중복을 어느정도 막아주기 때문에((1, 2), (1, 3) 탐색 후 (2, 1)을 다시 탐색하는 걸 방지하고 바로 (2, 3)으로 넘어감) 저게 더 짧을 거라 생각했는데 저거는 또 560ms 걸림 ㅋㅋ 아니 씨발 모르겠네
*/