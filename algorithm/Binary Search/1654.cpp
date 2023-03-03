#include <iostream>
#define MAX 10000

using namespace std;

int K, N;
long long lan[MAX];

bool check(long long length);

int main(){
  long long start = 1, end = 0, ans = 0;

  scanf("%d %d", &K, &N);

  for(int i=0; i<K; i++){
    scanf("%lld", &lan[i]);
    end = max(end, lan[i]);
  }

  while(start <= end){
    long long mid = (start+end)/2;

    if(check(mid)){
      ans = mid;
      start = mid+1;
    }
    else
      end = mid-1;
  }

  printf("%lld", ans);
  
  return 0;
}

bool check(long long length){
  long long count = 0;

  for(int i=0; i<K; i++)
    count += lan[i]/length;
  
  return (count >= N) ? true : false;
}

/*
마지막에 오버플로우 때문에 틀렸던 이진 탐색 문제. 문제는 간단한데, length 길이의 랜선을 N개 이상 만들 수 있는지 판단하는 함수인 check를 정의하고,
length를 1~max(lan) 내에서 이진탐색을 쳐줘서 check가 참이 되도록 하는 최대의 length를 찾아주면 된다. 2805-2와 거의 유사함.

다 풀었는데 오버플로우 때문에 좀 틀렸다. 처음에는 22행의 mid를 int로 했었는데, 그렇게 하니깐 start와 end를 더해주는 부분에서 int 범위를 초과하는
바람에 오버플로우가 났다. 근데 mid를 long long으로 고치고 나서도 오버플로우가 났는데, 아예 (start+end) 이 괄호 부분에서 바로 오버플로우가 
나버리면서 값이 음수가 되어버린다. 그래서 걍 start랑 end도 long long형으로 만들고 나니 맞았음.
*/