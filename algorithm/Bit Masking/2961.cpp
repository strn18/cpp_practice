#include <iostream>
#define MAX 10
#define INF 2100000000

using namespace std;

int main(){
  int N, full, min_diff = INF;
  int S[MAX], B[MAX];

  scanf("%d", &N);
  full = (1<<N)-1;
  for(int i=0; i<N; i++)
    scanf("%d %d", &S[i], &B[i]);

  for(int bit=1; bit<=full; bit++){
    int sour = 1, bitter = 0;

    for(int i=0; i<N; i++){
      if((bit>>i) & 1){
        sour *= S[i];
        bitter += B[i];
      }
    }

    min_diff = min(min_diff, ((sour-bitter > 0) ? sour-bitter : bitter-sour));
  }

  printf("%d", min_diff);

  return 0;
}

/*
쉬웠던 비트마스킹 문제. 16938과 거의 유사하다. N개의 재료가 있을 때, 재료를 고르는 모든 경우의 수를 탐색하고, 요리의 신맛과 쓴맛의 차이가 가장
작을 때 그 값을 출력하면 된다(단, 재료는 하나 이상 사용). 16938을 풀 때는, 함수를 이용하여 좀 약간 dfs 내지 탐색스럽게 풀었었는데, 이번에는
16938 다른 사람 풀이를 볼 때 보았던 방식대로 풀었다.

bit는 비트마스킹을 이용하여, 0~N-1번째 재료를 썼는지 안 썼는지를 나타낸다. 0번째 비트가 1이면 사용한 것이다. 이때 bit가 될 수 있는 값은,
1 ~ (1<<N)-1 이므로, 이 값을 모두 찾아보면서(즉, 재료의 조합을 모두 찾아보면서) 신맛과 쓴맛의 차가 최소일 때를 구해주면 된다.
17행에서 요리의 신맛인 sour는 1로, 쓴맛인 bitter는 0으로 초기화했는데, 요리의 신맛은 재료의 신맛의 곱과 같고, 쓴맛은 합과 같으니까 그렇다.
그런 다음, 19행에서 bit의 0~N-1번째 비트를 보면서, i번째 비트가 1이면(i번째 재료를 썼으면) i번째 재료의 신맛과 쓴맛을 곱해주고 더해준다.
*/