#include <iostream>
#define MAX 20

using namespace std;

typedef struct{int r, c;} pos;

int board[MAX][MAX];

int cut(pos start, pos end, int dir);
int count_func(pos start, pos end, int which);

int main(){
  int N, ans;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &board[i][j]);

  ans = cut({0, 0}, {N-1, N-1}, 0) + cut({0, 0}, {N-1, N-1}, 1);

  printf("%d", ans==0 ? -1 : ans);

  return 0;
}

int cut(pos start, pos end, int dir){
  int imp = count_func(start, end, 1);
  int jewel = count_func(start, end, 2);

  if(imp == 0){
    if(jewel == 1) return 1;
    else return 0;
  }
  if(jewel <= 1) return 0;

  int count = 0;
  
  if(dir == 0){
    for(int cut_r = start.r+1; cut_r <= end.r-1; cut_r++){
      if(count_func({cut_r, start.c}, {cut_r, end.c}, 1) && !count_func({cut_r, start.c}, {cut_r, end.c}, 2)){
        count += (cut(start, {cut_r-1, end.c}, 1) * cut({cut_r+1, start.c}, end, 1));
      }
    }
  }

  else{
    for(int cut_c = start.c+1; cut_c <= end.c-1; cut_c++){
      if(count_func({start.r, cut_c}, {end.r, cut_c}, 1) && !count_func({start.r, cut_c}, {end.r, cut_c}, 2)){
        count += (cut(start, {end.r, cut_c-1}, 0) * cut({start.r, cut_c+1}, end, 0));
      }
    }
  }

  return count;
}

int count_func(pos start, pos end, int which){
  int count = 0;

  for(int i=start.r; i<=end.r; i++)
    for(int j=start.c; j<=end.c; j++)
      if(board[i][j]==which)
        count++;

  return count;
}

/*
살짝 까다로웠지만 문제 제대로 이해하고 나니 어렵지 않게 풀었던 분할정복 문제.

처음에는, 석판을 자를 때, 이전에 가로로 잘랐다면 다음 번에는 세로로 자르고.. 이런 방식인 줄 알았다. 즉, 문제에 주어진 그림을 예로 들면, 반드시
1-2-4-3 이 순서로 잘라야 하는 줄 알았음(가로-세로-가로-세로). 대체 어떻게 푸는 건지 잘 모르겠어서 고민하다가 문제를 다시 읽어봤더니, 내가 잘못
이해했었다. 그냥 어떠한 석판이 있을 때, 이 석판을 이전에 가로로 잘랐다면(잘리기 전의 큰 조각을 가로로 잘라서 이 석판이 된 거라면) 이제 이 석판은
세로로 잘라야 하고, 세로로 잘랐다면 가로로 잘라야 하는 그런 방식이었다. 즉, 1번으로 먼저 잘랐다면, 위아래의 조각은 이제 세로로 잘라야 하고, 위의
조각을 다시 2번으로 잘랐다면, 그 오른쪽의 조각은 이제 가로로 잘라야 하는 그런 방식이라는 것.

이걸 이해하니까 좀 수월했다. 주어진 범위의 석판을 자르는 함수를 cut이라고 하면, 그 함수의 인자로 석판 범위 뿐만 아니라, 자를 방향(가로 or 세로)도
들어올테니까, 그거에 따라서 주어진 범위를 가로 or 세로로 다 시도해보고, 가능할 때(잘리는 부분에 불순물이 있고 보석이 없을 때) 다시 재귀적으로
cut을 실행해주면 된다. 이때, 잘리고서 생기는 두 부분에 대해서 cut을 실행해주고, 자를 방향은 방금 받은 거랑 반대값을 넣어주면 될 것이다.

이걸 토대로 cut 함수를 정의했다. 처음에는 start_r, start_c, end_r, end_c 이렇게 했었는데 귀찮아져서 그냥 구조체 정의해서 하나로 묶었다.
40행과 48행이 각각 가로로 자를 때와 세로로 자를 때이다. 가로로 자를 때를 설명하자면, 주어진 범위에서 첫 행과 마지막 행을 제외한 모든 행에 대해서,
그 행을 자를 수 있는지 없는지 판단해본다(42행. 그 행에 불순물 있고 보석 없어야함). 그 다음, 그 행을 기준으로 둘로 나눠서, 두 부분에 대해 다시 cut
함수를 실행해주고(이번엔 세로로), 그 두 값을 곱한 값을 count에 넣는다. 곱하는 이유는? 왼쪽과 오른쪽은 이제 독립적인 케이스니까, 곱의 법칙으로
곱해줘야 한다. 가령 위쪽을 자르는 경우의 수가 2가지이고, 아래쪽이 3가지라면, 총 경우의 수는 6가지니깐. 그리고, 84행에서 첫 행과 마지막 행을 
제외한 이유는? 문제 조건에 따르면, 잘라진 석판은 반드시 두 개의 석판이 나뉘어진 것이어야 한다고 했다. 근데 첫 행이나 마지막 행을 자르면, 두 부분이
안 나오니깐 제외했다. 여기까지가 가로로 자를 때인데, 세로로 자를 때도 그냥 방향만 다르고 똑같다.

그리고 29~36행은 기저조건 부분인데, 우선 주어진 범위에서 불순물과 보석의 개수를 모두 센다. 만약 불순물이 없는데, 보석이 1개라면? 최종적으로 석판을
다 잘 나눈 것이므로, 1을 리턴한다. 만약 보석이 1개가 아니라면? 잘못 나눈 거니까, 0을 리턴한다. 만약 불순물은 있는데, 보석이 0개나 1개라면? 
마찬가지로 잘못 나눈 것이므로 0을 리턴한다. 이 모든 경우에 해당이 안 될 때(불순물이 있고, 보석이 2개 이상), cut 함수를 재귀쳐서 더 나눠본다.

count_func 함수는 주어진 범위에서 불순물이나 보석을 세는 함수이다. 각각 which에 인자로 1과 2를 주면 셀 수 있음.
*/