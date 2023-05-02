#include <iostream>
#define MAX 12
#define PICK 6

using namespace std;

int k, S[MAX], num[PICK];

void choose(int n, int idx);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while(true){
    cin >> k;

    if(!k) break;

    for(int i=0; i<k; i++)
      cin >> S[i];

    choose(PICK, 0);
    cout << '\n';
  }

  return 0;
}

void choose(int n, int idx){
  if(n==0){
    for(int i=0; i<PICK; i++)
      cout << num[i] << ' ';
    cout << '\n';
    return;
  }

  for(int i=idx; i<k; i++){
    num[PICK-n] = S[i];
    choose(n-1, i+1);
  }
}

/*
오랜만에 풀어본 백트래킹 문제. choose 함수는 인덱스 idx부터 n개를 고르는 함수이다. 처음에 풀 때는(첫 제출), 배열 S에서 고를 수 있는 수가 x개
일 때, 앞으로 y개를 골라야 한다고 치면, x<y 이면 절대로 다 못 고르니까 그 경우를 배제해주기 위해 choose 함수의 for문의 조건 부분을 좀 다르게
했었다. 이번에 i번째 수를 골랐다면 다음 depth에서는 i+1번째 수부터 고를 수 있으므로 고를 수 있는 수는 k-(i+1)개이고, 골라야 하는 수는 n-1개이다
(1개 방금 골랐으므로). 그러므로, k-i<n 이라면 더 이상 볼 필요 없이 for문을 나오면 된다. 

다 풀고 맞고 나서 https://seoftware.tistory.com/97 여기를 보니까 그냥 그런 거 없이 i<k 로 조건부를 넣었음. 사실 이렇게만 해도, 어차피 위의
경우는 수를 6개까지 고를 수 없어서 알아서 걸러지긴 함.
*/