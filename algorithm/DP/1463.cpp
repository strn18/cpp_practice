#include <iostream>

using namespace std;

int num[1000001]={0, 0};
int dp(int n);

int main(){
  int N;
    
  scanf("%d", &N);
  printf("%d", dp(N));

  return 0;
}

int dp(int n){
  if(num[n]||n==1)
    return num[n];

  num[n] = dp(n-1)+1;
  if(!(n%3))
    num[n] = min(num[n], dp(n/3)+1);
  if(!(n%2))
    num[n] = min(num[n], dp(n/2)+1);
  return num[n];
}

/*
쉬운 DP문제. top-down 방식(재귀)으로 풀었다. 처음에는 num 배열 안 만들고 그냥 했는데 시간초과가 났다.
그래서 메모이제이션을 위해 num배열을 만들어 풀었더니 맞았음. 이후 코드를 좀 더 간소화해서 한 번 더 제출했다.
*/