#include <iostream>
#define MAX 100000

using namespace std;

int N, M;
int lec[MAX];

bool check(int S);

int main(){
  int ans, start, end = 0;

  scanf("%d %d", &N, &M);

  for(int i=0; i<N; i++){
    scanf("%d", &lec[i]);
    end += lec[i];
  }

  start = end/M;
  ans = end;

  while(start <= end){
    int mid = (start+end)/2;

    if(check(mid)){
      ans = mid;
      end = mid-1;
    }
    else
      start = mid+1;
  }

  printf("%d", ans);

  return 0;
}

bool check(int S){
  int filled = 0, count = 1;

  for(int i=0; i<N; i++){
    if(lec[i] > S) return false;
    
    if(filled+lec[i] > S){
      count++;
      filled = lec[i];
    }
    else
      filled += lec[i];
  }

  return (count <= M ? true : false);
}

/*
어렵지 않았던 매개변수 탐색 문제. 
"블루레이 개수가 M개일 때, 가능한 블루레이 크기의 최솟값"을 구하는 것은 어려우므로, 이를 결정 문제로 뒤집어서 "블루레이 크기를 S로 잡았을 때,
M개의 블루레이에 담을 수 있는가?"로 만들고 풀면 쉬워진다.

이때 S의 범위는 sum(lec)/M ~ sum(lec)이다. 최솟값이 sum(lec)/M인 이유는, 그거보다 작아지면 그 크기의 블루레이가 M개일 때, 크기의 총합이 
sum(lec)보다 작아지므로 반드시 불가능하다. 이 범위 내에서 S를 이분탐색으로 갱신해주면서, M개의 블루레이에 강의를 모두 담을 수 있는지를
check 함수를 통해 판별해주고, 가능하다면(27행) 답을 갱신한 후 탐색 범위를 현재 S값-1로 바꿔주고, 불가능하다면(31행) 탐색 범위를 현재 S값+1로 
바꿔준다.

check 함수는, 우선 현재 블루레이의 채워진 크기를 나타내는 filled 변수와, 사용한 블루레이의 개수를 나타내는 count 변수를 사용한다.
모든 강의를 순서대로 돌면서, 우선 만약 강의 크기가 S보다 크다면 바로 false를 리턴한다. 그렇지 않고, 만약 현재 블루레이에 이번 강의를 추가했을
때 S를 초과해버리면, 다음 블루레이를 사용해야 하므로, count를 증가시키고 filled에는 이번 강의의 크기를 넣어준다. 만약 S를 넘지 않을 경우,
이번 강의를 넣을 수 있으므로 filled에 이번 강의의 크기를 더해준다. 다 끝났을 때, 사용한 블루레이의 개수가 M보다 많으면 false를 리턴하고,
M 이하면 M개의 블루레이에 모든 강의를 넣을 수 있으므로 true를 리턴한다.
*/