#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> num;

int solve(void);
bool Compare(int a, int b){
  return a>b;
}

int main(){
  int N, temp, ans = 0;
  
  scanf("%d", &N);
  for(int i=0; i<N; i++){
    scanf("%d", &temp);
    num.push_back(temp);
  }

  sort(num.begin(), num.end());

  int start = N-1;
  for(int i=0; i<N; i++){
    if(num[i] > 1){
      start = i;
      break;
    }
  }
  sort(num.begin()+start, num.end(), Compare);

  while(num.size())
    ans += solve();

  printf("%d", ans);

  return 0;  
}

int solve(void){
  int cur = num[0];
  num.erase(num.begin());
  if(num.empty()) return cur;

  int next = num[0];
  if(cur < 0){
    if(next <= 0){
      cur *= next;
      num.erase(num.begin());
    }
  }
  else if(cur == 0){
    if(next == 0){
      cur *= next;
      num.erase(num.begin());
    }
  }
  // if cur == 1, then just return.
  else if(cur > 1){
    cur *= next;
    num.erase(num.begin());
  }

  return cur;
}

/*
어렵지 않았던 그리디 문제. 수열을 세 부류로 나눴다 치자. 1) 2 이상의 양수. 2) 음수. 3) 0과 1. 이때, 1)은 큰 놈들부터 둘씩 묶어서 곱하면 된다.
2)는 작은 놈들(절댓값이 큰 놈들)부터 둘씩 묶어서 곱하면 된다. 3) 0은 지들끼리 곱하거나, 2)에서 둘씩 묶은 다음 남는 놈이 있다면 걔랑 곱하면
된다. 1은 음수와 곱해도 손해, 0과 곱해도 손해, 1과 곱해도 손해, 2 이상의 양수와 곱해도 손해니까, 묶지 말고 그냥 더해준다.
이 작업을 수열의 각 수에 대해 수행해주면 된다.
처음에는 입력값을 위의 세 부류로 나눠서, 음수 담는 배열, 양수 담는 배열, 0과 1의 개수를 저장하는 변수. 이렇게 셋으로 나눠서 저장할까 했는데,
생각해보니 귀찮을 것 같아서 그냥 num 배열에 다 받았다. 그 다음, 오름차순으로 정렬해준다. 그리고 벡터의 맨 앞부터 시작하면서, 위의 작업을 
수행해준다. 이때, 수가 오름차순으로 정렬되어있기에, 맨 앞의 수가 2 이상의 양수라면, 큰 놈들부터 둘씩 묶어서 곱하는 작업을 해줄 수가 없다.
그렇기에, 오름차순으로 했을 때 2 이상의 양수가 들어있는 위치부터는 내림차순으로 정렬해준다(32행 / 큰 놈들부터 봐야하니깐). 
벡터의 맨 앞의 수와 그 다음 수를 이용해서 작업을 수행해주면 된다.

다른 풀이들 보니까 다들 내가 처음에 하려던 방식(음수, 양수, 0과 1로 나누는 방식)으로 풀었네.

이 문제 풀면서 vector.erase(위치)의 인자인 '위치'가 인덱스가 아니라, 지우고 싶은 부분의 주솟값 그 자체라는 걸 알았음. 즉 vector[2] 부분을 지우고
싶다면 vector.erase(2)가 아니라 vector.erase(vector.begin()+2) 이렇게 해줘야함.
*/