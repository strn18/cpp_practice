#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct{int s, e;} time;

bool Start_ascend(time meet1, time meet2){
  return meet1.s < meet2.s;
}
bool End_ascend(time meet1, time meet2){
  return meet1.e < meet2.e;
}

int main(){
  int N, a, b;
  int end_time = 0, count = 0;
  vector<time> meetings;

  scanf("%d", &N);
  for(int i=0; i<N; i++){
    scanf("%d %d", &a, &b);
    meetings.push_back({a, b});
  }

  sort(meetings.begin(), meetings.end(), Start_ascend);
  sort(meetings.begin(), meetings.end(), End_ascend);

  for(int i=0; i<N; i++){
    if(meetings[i].s >= end_time){
      end_time = meetings[i].e;
      count++;
    }
  }

  printf("%d", count);
  
  return 0;  
}

/*
다시 풀어봤던 그리디 문제. 원래는 파이썬으로 풀었는데, 벡터와 구조체(회의 시작 시간, 종료 시간으로 이루어짐)를 사용해서 풀었다.
시작 시간 기준 오름차순 한 번, 종료 시간 기준 오름차순 한 번 정렬하여 푸는 방식 그대로 c++로 했다.
*/