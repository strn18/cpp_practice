#include <iostream>
#include <vector>
#define MAX 4000000

using namespace std;

bool not_prime[MAX+1] = {false};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, count = 0;
  vector<int> prime = {0}; // prime[1]: 1번째 소수(2)
  vector<long long> p_sum = {0}; // p_sum[i]: 1~i번째 소수의 합

  cin >> N;

  for(int i=2; i<=MAX; i++){
    if(!not_prime[i]){
      prime.push_back(i);

      for(int j=2; i*j<=MAX; j++)
        not_prime[i*j] = true;
    }
  }

  for(int i=1; i<prime.size(); i++)
    p_sum.push_back(p_sum[i-1]+prime[i]);

  int s = 1, e = 1;

  while(s<=e){
    long long sum = p_sum[e]-p_sum[s-1];

    if(sum == N) count++;

    if(sum > N || e == prime.size()-1) s++;
    else e++;
  }

  cout << count;

  return 0;
}

/*
어렵지 않았던 투 포인터 + 부분합 문제(근데 사실 부분합은 필요 없었음). 

우선, 에라토스테네스의 체를 이용하여, [1, 400만]의 모든 소수를 찾고, 이를 prime 벡터에 넣는다. 그런 다음, prime 벡터의 부분합을 나타내는
p_sum 벡터를 만들고 값을 넣는다(이때, p_sum[i] = 1~i번째 소수의 합. 이 된다. 1-base를 하기 위해서 14, 15행에서 벡터 선언과 동시에 인덱스 0의
값으로 0을 넣어주었다).

그런 다음, 투 포인터를 이용한다. s와 e를 1부터 시작하여, s~e번째 소수의 합을 sum이라고 두고, 이것이 N과 같으면? count를 증가시킨다. 만약
이것이 N보다 크다면? sum이 줄어들어야 하니까, s를 증가시킨다. N보다 작거나 같다면? 반대로 e를 증가시킨다. 여기에 더해서, 만약 e가 벡터의
인덱스의 끝에 도달했다면? 그때도 무조건 s를 증가시킨다.

이걸 s<=e인 한 반복해서, count를 구한다.

나는 이렇게 풀었는데, 우선 개선점이 조금 있었음. 일단 내가 생각해냈던 걸로는, 주어진 수가 N일 때, 무작정 [2, 400만]에 대해서 모든 소수를 찾을
필요는 없다. N/2 이상인, 첫번째 소수까지만 찾아주면 됨. 왜냐? 연속된 소수의 합인데, N/2 이상인 소수 두 개를 합치면 반드시 그 합이 N보다 커지니까,
그 위로는 찾을 필요 없음. 그치만 N/2 이상인, 첫번째 소수 까지는 찾아야 하는데, N/2 미만인 소수랑 그거랑 합쳐서 N은 될 수 있기 때문.
ex) N = 12라면? 5+7 = 12이다. 7은 6 이상인 첫번째 소수임. 딱 거기까지만 찾아주면 된다.
이걸 알기는 했는데, 구현하려니 귀찮아서 그냥 400만까지 다 찾았다. 그래도 시간 초과 안 나니 괜찮음.

그리고 또 하나로, 나는 부분합으로 풀었는데 https://primayy.tistory.com/34 여기를 보니까 부분합을 쓸 필요가 없다. 그냥 prime까지만 구해놓고,
s와 e를 변동시킬 때마다 sum값에 직접 더해주거나 빼주면 됨. 

이거 외에도, 19행이랑 23행에서, MAX까지 다 찾는 게 아니라 N까지만 찾는 그런 방법도 있는데, 직접 제출해보니깐 시간은 차이 없었다. 그리고 
not_prime을 배열 말고 벡터로 써서 애초에 선언할 때 길이 N+1, 값은 false로 선언하는 방법도 해봤는데 시간이 오히려 조금 늘어남. 벡터라 그런듯
*/