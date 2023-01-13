#include <iostream>

using namespace std;

int N;
int first[4]={2, 3, 5, 7}, after[4]={1, 3, 7, 9}; // 1번째 자리에 올 수 있는 수, 2~N번째 자리에 올 수 있는 수

bool isPrime(int n);
void solve(int target, int n);

int main(){
  scanf("%d", &N);

  solve(0, 1);

  return 0;
}

bool isPrime(int n){
  for(int i=2; i<=n/2; i++)
    if((n%i)==0)
      return false;
  return true;
}

void solve(int target, int n){
  if(n==1){
    for(int i=0; i<4; i++){
      target+=first[i];

      if(n==N)
        printf("%d\n", target);
      else
        solve(target*10, n+1);

      target-=first[i];
    }
  }
  else{
    for(int i=0; i<4; i++){
      target+=after[i];

      if(isPrime(target)){
        if(n==N)
          printf("%d\n", target);
        else
          solve(target*10, n+1);
      }

      target-=after[i];
    }
  }
}


/*
겉보기에는 좀 까다로워보였지만 사실 별로 안 어려웠던 백트래킹 문제.
처음에는 1~2자리부터 최대 8자리의 수까지 계속해서 소수 판별을 해야 하길래, 탐색해야하는 가짓수(2에서 21, 22, ..., 29로 가고,
21에서 또 211, 212, ..., 219로 가고 등등)도 많은데 그냥 isPrime 함수를 짜면 계산 횟수가 너무 많아서 시간초과가 날 줄 알았다.
그래서 에라토스테네스의 체를 이용해서 미리 8자리까지 모든 소수를 찾아서 벡터에 넣어야하나 싶었다.
근데 예제를 잘 보니까 2~N번째 자리는 무조건 1 3 7 9 중에 있다(왜냐면 1번째 자리부터 해당 자리까지 소수여야 하는데, 해당 자리 수가 
짝수면 2로 나눠지니까 소수일 수 없고, 5면 5의 배수가 되니까 마찬가지로 소수일 수 없다)는 걸 인지했고, 1번째 자리는 당연히 2 3 5 7 중에 있으니까
탐색해야하는 가짓수가 많이 줄어들 것이라고 생각했고 그냥 isPrime 함수를 짜고 각 자리마다 4가지 가지를 탐색하는 식으로 짜서 쉽게 풀었다.
다만 21행을 원래 if(!n%i) 이렇게 했었는데 isPrime 결과가 자꾸 이상하게 나왔음 아마 !(n%i) <- 이렇게 계산하는게 아니라 
(!n)%i 이렇게 계산되어서 그런듯.. 괄호 잘 쳐주니까 결과 제대로 나옴
*/