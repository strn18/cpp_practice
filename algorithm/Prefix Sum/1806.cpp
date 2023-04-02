#include <iostream>
#define MAX 100000

using namespace std;

int N, S;
int num[MAX], sum[MAX] = {0};

bool check(int L);

int main(){
  scanf("%d %d", &N, &S);

  for(int i=0; i<N; i++)
    scanf("%d", &num[i]);
  
  sum[0] = num[0];
  for(int i=1; i<N; i++)
    sum[i] = sum[i-1] + num[i];

  int low = 1, high = N;
  int ans = 0;

  while(low <= high){
    int mid = (low + high)/2;

    if(check(mid)){
      ans = mid;
      high = mid-1;
    }
    else
      low = mid+1;
  }

  printf("%d", ans);

  return 0;
}

bool check(int L){
  if(sum[L-1] >= S) return true;

  for(int i=L; i<N; i++)
    if(sum[i] - sum[i-L] >= S) return true;
  
  return false;
}

/*
처음 풀어본 누적 합(부분 합) 문제. 

누적 합의 길이가 1일 때부터 최대 N일 때까지 하나하나 다 찾아보려고 하면, 약 O(N*N)의 계산이 필요해서(어떠한 길이를 정해놨을 때, 그 길이의 모든
누적 합을 구하면 약 N번이고, 길이는 1부터 N까지 총 N개이므로), 시간초과가 난다. 그래서 어떻게 풀까 고민하다가, 매개변수 탐색(이분 탐색) 방식을
적용해서 풀었다. 누적 합의 길이를 L이라고 했을 때, L을 최솟값인 1부터 최댓값인 N 사이에서 이분 탐색을 해주면서, 누적 합이 S 이상인, 최소의 
길이를 찾는다. 누적 합이 S 이상인지 확인하는 함수는 check 함수이다. 이 값이 참이면 high = mid-1 을 해줘서 더 작은 길이에서 이분 탐색을 해주고,
값이 false면 low = mid+1 을 해줘서 더 긴 길이에서 이분 탐색을 해준다.

나는 이렇게 풀어서 당연히 매개변수 탐색+누적 합 문제인 줄 알았는데, 알고리즘 분류를 보니까 투 포인터 문제였다. 투 포인터란, 두 개의 포인터를
조작하면서, 절대 답이 되지 않는 경우는 계산하지 않음으로써 시간을 단축시키면서 원하는 것을 얻는 알고리즘이라고 한다. 
https://danidani-de.tistory.com/2 여기에서의 투 포인터에 대한 설명처럼, https://danidani-de.tistory.com/3 여기서 start와 end라는 두
포인터를 둘 다 0(인덱스)에서 시작하여, start부터 end까지의 누적 합이 S 이상이면 min_Len을 갱신해주고 start++을 해주고, 그렇지 않으면 end++을
해주는 방식이다. 

채점 현황을 보니까 내 방식과 풀이 시간에는 큰 차이가 없었지만, 내 방식은 O(NlogN) 정도인데 이 방식은 O(N) 정도였다. 다음 번에는 투 포인터
한 번 풀어봐야 할듯.
*/