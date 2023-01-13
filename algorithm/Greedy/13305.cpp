#include <iostream>

using namespace std;

int N;
long long road[99999], price[100000];

int Find_low_price_city(int cur); // cur번 도시의 오른쪽 도시 중, 
// 기름 가격이 cur번 도시보다 낮고, 가장 왼쪽에 있는 도시의 번호를 리턴한다.
// 만약 없다면, 제일 오른쪽 도시의 번호를 리턴한다.

int main(){
  int cur = 0;
  long long cost = 0;

  scanf("%d", &N);

  for(int i=0; i<N-1; i++)
    scanf("%lld", &road[i]);
  for(int i=0; i<N; i++)
    scanf("%lld", &price[i]);

  while(cur != N-1){
    int next = Find_low_price_city(cur);

    for(int i=cur; i<next; i++)
      cost += price[cur]*road[i];

    cur = next;
  }
  
  printf("%lld", cost);

  return 0;  
}

int Find_low_price_city(int cur){
  for(int i=cur+1; i<N-1; i++)
    if(price[i] < price[cur])
      return i;
  return N-1;
}

/*
어렵지 않았던 그리디 문제. 어떠한 도시에서는, 그 오른쪽에 있는 도시들 중에 기름 가격이 더 낮은 도시에 도달할 만큼만 기름을 채워주면 된다.
이를 위해 Find_low_price_city 함수를 정의했는데, 이 함수는 인자로 받은 cur 도시에서 오른쪽의 도시들 중에서, 기름 가격이 cur 도시보다
더 낮은 도시들 중 제일 왼쪽에 있는 도시(가장 빨리 도달하게 되는)의 번호를 리턴한다. 만약 없다면, 현재 도시의 기름 가격이 최소인거니까,
마지막 도시에 갈 때까지의 기름을 다 채워주면 된다. 그렇기에, 그럴 경우에는 N-1(마지막 도시의 번호)를 리턴한다.
이후, Find_low_price_city 함수로 받은 도시 번호인 next를 이용하여, 현재 도시에서 next번 도시까지의 거리에 현재 도시의 기름 가격을 곱해서
그걸 cost에 더해주면 된다. 
참고로, 도시의 총 거리는 최대 10억이고, 리터당 가격은 최대 10억이라서 int로는 부족하다. 그렇기에 long long을 사용했다.
*/