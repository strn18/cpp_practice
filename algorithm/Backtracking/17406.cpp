#include <iostream>
#include <algorithm>

using namespace std;

int N, M, K, min_val = 9999;
int arr[51][51]; // 1-base
int rot[6][3]; // 회전 연산 정보
int used[6] = {0}; // 회전 연산을 사용했다면 1

void solve(int arr[][51], int n); // arr에 n번째 회전 연산을 적용시키기
void rotate(int arr[][51], int r, int c, int s); // arr를 회전 연산하기
int arr_val(int arr[][51]); // 배열 arr의 값 리턴

int main(){
  scanf("%d %d %d", &N, &M, &K);

  for(int i=1; i<=N; i++)
    for(int j=1; j<=M; j++)
      scanf("%d", &arr[i][j]);

  for(int i=0; i<K; i++)
    scanf("%d %d %d", &rot[i][0], &rot[i][1], &rot[i][2]);
    
  solve(arr, 1);
  printf("%d", min_val);

  return 0;
}

void solve(int arr[][51], int n){
  for(int i=0; i<K; i++){
    if(!used[i]){
      int new_arr[51][51];
      copy(&arr[0][0], &arr[0][0]+2601, &new_arr[0][0]);
      rotate(new_arr, rot[i][0], rot[i][1], rot[i][2]);
      used[i] = 1;
      if(n == K)
        min_val = min(min_val, arr_val(new_arr));
      else
        solve(new_arr, n+1);
      used[i] = 0;
    }
  }
}

void rotate(int arr[][51], int r, int c, int s){
  int count = 0;
  int temp[51][51];
  copy(&arr[0][0], &arr[0][0]+2601, &temp[0][0]);

  for(int i=(r-s); i<=(r+s); i++){
    if(i<=r){
      for(int j=(c-s); j<=(c+s); j++){
        if(i == r && j == c)
          continue;

        if(j <= (c-s)+count)
          arr[i][j] = temp[i+1][j]; // 아랫칸
        else if(j > (c+s)-count)
          arr[i][j] = temp[i-1][j]; // 윗칸
        else
          arr[i][j] = temp[i][j-1]; // 왼쪽칸
      }
      if(i != r)
        count++;
      else
        count--;
    }
    else{
      for(int j=(c-s); j<=(c+s); j++){
        if(j < (c-s)+count)
          arr[i][j] = temp[i+1][j]; // 아랫칸
        else if(j >= (c+s)-count)
          arr[i][j] = temp[i-1][j]; // 윗칸
        else
          arr[i][j] = temp[i][j+1]; // 오른쪽칸
      }
      count--;
    }
  }  
}

int arr_val(int arr[][51]){
  int minimum = 9999;
  for(int i=1; i<=N; i++){
    int count = 0;
    for(int j=1; j<=M; j++)
      count += arr[i][j];
    minimum = min(minimum, count);
  }
  return minimum;
}

/*
전체적인 구조는 쉬웠으나 배열을 시계 방향으로 1칸 회전하는 함수인 rotate의 구현이 살짝 까다로웠던 문제. 
큰 구조는 그냥 배열에 1번부터 K번 회전 연산을 모든 순서(K!가지)로 적용을 시키고, 최종 배열의 값이 가장 작을 때 그걸 구하면 되어서 어렵지 않았지만
rotate의 함수가 보기에는 쉬우나 막상 구현하려니 조금 까다로웠다. 고민 좀 하다가 별 찍기 문제와 비슷한 방식으로 구현을 했는데,
*****
 ***
  *
 ***
*****
이런 모양의 별 찍기를 할 때 1) 별의 좌측, 2) 별, 3) 별의 우측. 이 세 부분을 따로 처리해주는 것처럼
여기서는 count라는 변수를 따로 만들어서 그걸 0 1 2 1 0 이런 순서로 변화시키면서, 그걸 이용해서
1) 아랫칸 값 가져오기, 2) 왼쪽칸 값 가져오기, 3) 윗칸 값 가져오기. 이 세 부분을 if문으로 따로 처리했다.
그리고 중간 행을 넘어가면서부터는 2)가 왼쪽칸이 아닌 오른쪽 칸의 값을 가져오도록 변화시켰음. 자세한건 rotate 함수 참조
*/