#include <iostream>
#define INF 1000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, cost = 0;
  int min_set_cost = INF, min_one_cost = INF;

  cin >> N >> M;

  for(int i=0; i<M; i++){
    int set, one;

    cin >> set >> one;

    min_set_cost = min(min_set_cost, set);
    min_one_cost = min(min_one_cost, one);
  }

  if(min_set_cost < 6*min_one_cost){
    int set_num = N/6;
    int rest = N-(set_num*6);

    cost += set_num*min_set_cost;

    if(rest != 0) cost += min(rest*min_one_cost, min_set_cost);
  }
  else cost += N * min_one_cost;

  cout << cost;

  return 0;
}

/*
쉬운 그리디 문제. 세트와 낱개의 최소 가격을 찾고, 가성비가 세트가 더 좋을 경우, 세트를 최대한 쓰고 남는 거는 낱개를 사는 거랑, 그 남는 거까지 걍 
세트로 사는 것 중에 더 싼 가격을 찾는다. 가성비가 낱개가 더 좋으면 다 낱개로 사면 된다.
*/