#include <iostream>
#include <queue>
#define MAX 1000000

using namespace std;

int price[MAX], max_price[MAX]; // max_price[i]: price[i]~price[N-1] 중 최댓값

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int N, bought = 0;
    long long total = 0;

    cin >> N;

    for(int i=0; i<N; i++)
      cin >> price[i];
    
    max_price[N-1] = price[N-1];

    for(int i=N-2; i>=0; i--){
      if(price[i] > max_price[i+1]) max_price[i] = price[i];
      else max_price[i] = max_price[i+1];
    }

    for(int i=0; i<N; i++){
      if(price[i] == max_price[i]){
        total += (bought * price[i]);
        bought = 0;
      }
      else{
        total -= price[i];
        bought++;
      }
    }

    cout << total << '\n';
  }

  return 0;
}

/*
은근 까다로웠던 문제.

풀이법 떠올리기는 어렵지 않았다. 0일부터 돌면서, 만약 i일이 0일 ~ N-1일 중 주식 값이 최고점인 날이라면 가진 주식을 모두 팔면 되고, 그렇지 않으면 
주식을 산다. 주식을 팔고 나면, 다시 i+1일부터 돌면서, 만약 j일이 i+1일 ~ N-1일 중 ... 이렇게 위의 과정을 끝까지 반복하면 된다.

그래서 대충 구현해서 제출했더니 시간초과가 났다. 왜 났나 했는데, 만약 주식 가격이 10 9 8 7 ... 이런 형태라면? 우선 첫날, 그게 최고점인 날인지 
판단하기 위해 0일 ~ 마지막일 까지 돌면서 max값을 찾는다. 최고점인 날이니까 팔고, 다시 둘째날도 똑같이 1일 ~ 마지막일 도는 걸 반복... 이렇게 
되어서, 결국 O(N^2)이 되는 것이다.

어떻게 할지 고민하다가 한 번 뇌절쳐서 pq로 했었는데 될 리가 없음.. 만약 i일에서 최고점이면, 가격들이 들어가있는 pq에서 최고점인 날의 가격은 
물론이고, 0일 ~ i-1일의 가격까지 모두 pop해야 하는데 될 리가 없다.

그래서 고민 좀 하다가, 마치 부분합처럼 푸는 방법 고안함. 배열 max_price를 만들었는데, max_price[i]는 price[i]~price[N-1] 중 최댓값을 
의미한다. 우선 price를 모두 입력받은 후, 28행의 과정을 해주면 된다(max_price[N-1]은 반드시 price[N-1]이므로 예외 처리함).

이렇게 max_price를 구했으면, 위에서 한 방법 그대로 해주면 시간초과 없이 끝낼 수 있다. 아까는 i일 ~ N-1일의 최고가를 찾기 위해 O(N)을 
돌렸는데, 이젠 O(1)로 구할 수 있으니 시간 초과 안 남.

다른 풀이들 보니깐, 뒤에서부터(마지막 날부터) 계산하는 방식이 많았다. 내 풀이랑 비슷한 느낌임
*/