// 사탕 가방(11. 이분탐색)
#include <iostream>
#define MAX 100
#define INF 1000000000000000000

using namespace std;

int N;
long long M;
long long candy[MAX];

bool make_bags(long long k); // k개의 가방을 만들 수 있으면 true

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    cin >> N >> M;

    for(int i=0; i<N; i++)
      cin >> candy[i];
    
    long long ans = 0, low = 1, high = INF;

    while(low <= high){
      long long mid = (low+high)/2;

      if(make_bags(mid)){
        ans = mid;
        low = mid+1;
      }
      else
        high = mid-1;
    }

    cout << '#' << t << ' ' << ans << '\n';
  }

  return 0;
}

bool make_bags(long long k){
  long long count = 0;

  for(int i=0; i<N; i++){
    count += candy[i]/k;

    if(count >= M) return true;
  }

  return false;
}

/*
쉬웠던 매개변수 탐색 문제. 주어진 문제를 "k개의 사탕 가방을 만드는 것이 가능한가?"로 바꾼 다음, 매개변수 탐색으로 가능한 k의 최댓값을 찾으면 됨. 

make_bags가 이를 검사한다. 각 종류의 사탕들에 대해서, 그 개수인 candy[i]를 k로 나눈 몫을 count에 계속 더한다. 왜냐? 일단 주어진 사탕 candy[i]개에 
대해서, 그걸 최대한으로 끌어다 써서 k개의 가방에 균일하게 담으면 되기 때문, 가령, candy[0] = 6894이고, k = 1000이라면, 1000개의 가방에 6개씩 
최대한으로 다 담는다. 그런 다음, candy[1] = 3441이면, 이번엔 3개씩 담고, ... 이런 식으로 최대한 다 담을 때, 각 가방 별로 담긴 개수인 count가 
M 이상이 된다면? k개의 가방을 만들 수 있는 것이고, 그렇지 않다면 만들 수 없음. 
*/