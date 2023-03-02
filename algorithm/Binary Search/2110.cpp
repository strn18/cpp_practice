#include <iostream>
#include <algorithm>
#define MAX 200000

using namespace std;

int N, C;
int house[MAX];

bool check(int d);

int main(){
  int ans = 0;
  
  scanf("%d %d", &N, &C);
  for(int i=0; i<N; i++)
    scanf("%d", &house[i]);
  
  sort(house, house+N);

  int start = 1, end = (house[N-1]-house[0]) / (C-1);
  while(start<=end){
    int mid = (start+end)/2;

    if(check(mid)){
      ans = max(ans, mid);
      start = mid+1;
    }
    else
      end = mid-1;
  }

  printf("%d", ans);
  
  return 0;
}

bool check(int d){
  int prev_house_idx = 0;

  for(int i=1; i<C; i++){
    bool flag = false;
    
    for(int j=prev_house_idx+1; j<N; j++){
      if(house[j]-house[prev_house_idx] >= d){
        prev_house_idx = j;
        flag = true;
        break;
      }
    }

    if(!flag) return false;
  }

  return true;
}

/*
쫌 어려웠던 이진 탐색 + 매개변수 탐색 문제. 설치할 공유기의 개수는 최소 2개이기에, C개의 공유기 중 우선 2개는 좌우 양 끝에 깔아두고 시작하는
방식으로 생각해봤다. 0~N-1번째 집 중에 중간(N/2번째)에 다음 공유기를 놓고(이진탐색 방식), 그 공유기가 그 위치일 때 다른 공유기를 최적의 위치
(가장 인접한 두 공유기 사이의 거리가 최대가 되도록)로 놓고, 다시 중간에 놨던 공유기를 왼쪽이나 오른쪽의 절반에 놓고 또 그 때의 다른 공유기를
최적의 위치에 놓고... 이런 방식으로 풀어야 하나 생각을 했었는데, 아무리 생각해도 잘 떠오르지 않았음.

그래서 https://scshim.tistory.com/495 여기를 좀 참고했다. "뒤집은 문제: 어떤 거리 만큼 거리를 둘 때, 공유기 C개를 설치할 수 있는가? Yes/No"
이 부분을 보고 좀 깨달았다. '공유기 C개를 어떻게 하면 최대한 거리 두도록 둘 수 있을까?'가 아니라, 'd만큼 거리 두도록 공유기 C개를 놓을 수
있을까?'로 바꾸는 건데, 그렇게 바꾸니 풀기가 훨씬 수월해짐. 이렇게 하니까 마치 2805번을 풀 때처럼, d를 1부터 최댓값 사이로 이진탐색을 치면서,
공유기 C개를 d만큼 거리 둘 수 있을 때 d의 최댓값을 찾으면 된다.

이때 시간복잡도는? 우선 d가 1과 최댓값 사이일 때 이진탐색하는데, 가장 인접한 두 공유기 사이의 거리는 (max(house)-min(house)) / (C-1)를 넘을
수 없다. 왜냐? 가령 집이 1 2 4 7 15이고, C가 3이라면, 공유기를 아무리 잘 놔봤자, max(house)가 15이고 min(house)가 1이니깐, (15-1)/2 = 7을
못 넘는다(7이 되도록 하려면 공유기 3개를 1 8 15 이렇게 놔야겠지). 집의 좌표는 0에서 10억이고 C는 최소 2가 될 수 있으니, 1부터 10억을 
이진탐색하면 log(10억) = 수십 정도가 된다.

그리고 각 이진탐색 절차에서, 공유기를 놓을 수 있는지 확인해야 하는데, 각 집(위치순으로 오름차순 정렬되었다고 가정)을 순차적으로 돌면서 d만큼
거리 두도록 놓을 것이므로, 총 N번 돌게 된다.

최종적으로 시간복잡도는, N*log(10억) = 수백만 정도가 되어서 가능하다(물론 N개의 각 집을 정렬하는 과정 때문에 +N*logN을 또 해야하긴 함).

21행에서 start값과 end값을 정해주고, start가 end 이하인 한 계속 탐색해준다. 만약 그 중간인 mid만큼 거리 둘 때 공유기 C개를 놓을 수 있다면,
답을 갱신해주고, 더 먼 거리로 거리 둘 수 있는지 확인해야 하므로 start를 mid+1로 갱신해준다. 만약 놓을 수 없다면, 더 짧은 거리로 거리 둬야
하므로 end를 mid-1로 갱신해준다.

check는 C개의 공유기를 d만큼 거리 둘 수 있는지 확인하는 함수이다. 우선 맨 처음 공유기는 house[0]에 놓을 거니까, prev_house_idx는 0으로
잡아준다. 그 다음, 나머지 C-1개의 공유기를 돌면서, 그 안에서 다시 prev_house_idx+1 ~ N-1번째 house를 돈다. 만약 이번 house와 
prev_house_idx번째 house(바로 이전의 공유기를 놓은 곳)의 위치 차이가 d 이상이라면 놓고 flag를 세우고 탈출. house를 다 돌았는데 flag가
아직 false면 이번 공유기를 놓을 집을 못 찾았으니까 false를 리턴. 맨 밑까지 왔으면 true를 리턴한다.

이렇게 풀어서 제출하니 맞았다. 위의 링크에 달린 풀이는 좀 달랐는데, 나는 C개의 공유기를 d만큼 거리 둘 수 있는지?를 판별했지만, 링크에서는
d만큼 거리 둘 때, 놓을 수 있는 공유기의 개수가 C개 이상인지?를 판별하는 방식이었다. 사실 거의 비슷한듯. 링크 풀이가 좀 더 간결하긴 하다.

2805 이후로 처음 풀어보는 난이도 있는 매개변수 탐색 문제였다.
*/