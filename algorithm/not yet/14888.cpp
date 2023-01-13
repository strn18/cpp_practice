/*
#include <iostream>

using namespace std;

int N, max_val = -1000000001, min_val = 1000000001;

int num[11];
int oper[4];

void F(int oper_index, int cur_val); // oper_index번째 연산자 판단 중이며, 현재까지의 값은 cur_val
int New_value(int cur_val, int oper, int next_num);

int main(){
  cin >> N;

  for(int i=0; i<N; i++)
    cin >> num[i];
  for(int i=0; i<4; i++)
    cin >> oper[i];

  F(0, num[0]);

  cout << max_val << endl << min_val;

  return 0;
}

void F(int oper_index, int cur_val){
  int next_val;

  for(int i=0; i<4; i++){
    if(oper[i]){ // 해당 연산자가 남아있다면
      oper[i]--; // 쓴다
      next_val = New_value(cur_val, i, num[oper_index+1]); // 값 갱신
      
      if(oper_index == N-2){ // 끝이라면 최댓값과 최솟값 갱신
        max_val = max(max_val, next_val);
        min_val = min(min_val, next_val);
        oper[i]++; // 쓴 연산자 다시 돌려놓고 리턴
        return;
      }
      F(oper_index+1, next_val); // 다음 위치 연산자 판단
      oper[i]++; // 이번 위치에서 쓴 연산자 다시 돌려놓기
    }
  }
}

int New_value(int cur_val, int oper, int next_num){
  switch(oper){
    case 0:
      return cur_val+next_num;
    case 1:
      return cur_val-next_num;
    case 2:
      return cur_val*next_num;
    case 3:
      return cur_val/next_num;
  }
}

스터디에서 백트래킹 강의 끝부분에 소개했던 문제. 근데 왜 백트래킹인지는 모르겠다 가지치기 없이 브루트포스로 풀어도 시간 0ms 나오는데.. 아마 최적화하는 방법을 다음 강의에서 알려주거나 할듯
*/