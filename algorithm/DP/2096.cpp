#include <iostream>
#include <algorithm>

using namespace std;

int dp_max[3], dp_min[3], temp[3], point[3];

int main(){
  int N;

  scanf("%d", &N);

  for(int j=0; j<3; j++){
    scanf("%d", &point[j]);
    dp_max[j] = point[j];
    dp_min[j] = point[j];
  }

  for(int i=1; i<N; i++){
    scanf("%d %d %d", &point[0], &point[1], &point[2]);

    temp[0] = max(dp_max[0], dp_max[1]) + point[0];
    temp[1] = max({dp_max[0], dp_max[1], dp_max[2]}) + point[1];
    temp[2] = max(dp_max[1], dp_max[2]) + point[2];
    for(int j=0; j<3; j++)
      dp_max[j] = temp[j];

    temp[0] = min(dp_min[0], dp_min[1]) + point[0];
    temp[1] = min({dp_min[0], dp_min[1], dp_min[2]}) + point[1];
    temp[2] = min(dp_min[1], dp_min[2]) + point[2];
    for(int j=0; j<3; j++)
      dp_min[j] = temp[j];
  }
  
  printf("%d ", max({dp_max[0], dp_max[1], dp_max[2]}));
  printf("%d ", min({dp_min[0], dp_min[1], dp_min[2]}));
  
  return 0;  
}

/*
개좃밥이지만 ㅈ같았던 문제.. 우선 문제 풀이 자체는 쉬웠음. 그냥 dp[i][j] = i행 j열의 점수를 먹었을 때, 지금까지 먹은 최대/최소 점수.로 둔 다음,
dp[i][0] = max(dp[i-1][0], dp[i-1][1]) + point[i][0] 이런 식으로, 내려올 수 있는 윗 행의 dp값 중 최대/최소를 골라 거기에 이번 칸의 점수를 
더해주면 된다. 근데 첫 제출에서 메모리초과가 떴다. 아하 dp_max, dp_min 그리고 point까지 총 3개의 배열이 각각 10만*3의 크기니까, 총 90만의 크기이고,
int 배열이니깐 4바이트*90만 = 360만 바이트 = 약 3.6 MB인데, 문제 메모리 제한이 4 MB여서 메모리초과가 나는구나 싶어서, dp를 max와 min로 나누지 않고
그냥 하나만 선언한 후, 어차피 시간제한은 널널하니까 최댓값으로 한 번, 최솟값으로 한 번 갱신하기로 했다. 그렇게 되면 30만 크기의 배열이 두 개이고,
총 4바이트*60만 = 약 2.4 MB로, 충분할 것이라 생각했음.
근데 또 메모리초과. 왜지? 싶어서 고민하다가 그냥 dp를 int dp[3]으로 크기 3짜리로 만들어놓고, 계속해서 갱신해주는 식으로 바꿨다.
그랬더니 맞았다고 뜸. 
https://yhwan.tistory.com/14 여기를 보니깐, 애초에 point도 10만*3의 크기로 할 필요가 없다. 그냥 매번 입력받을 때마다 크기 3짜리인 dp_max와
dp_min을 계속 갱신해주면 됨. 그렇게 해서 바꾸고 제출하니깐 메모리와 시간이 둘 다 줄었다.
의문을 품었던 메모리 관련해서 질문올렸는데, C++ 자체에서 1~2 MB 정도 사용한다고 한다. iostream 사용 시 2MB, 미사용 시 1MB 정도 쓴다고 함.
그래서 2.4 MB로도 메모리초과가 났나보다.
*/