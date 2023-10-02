#include <iostream>
#include <unordered_map>
#define ll long long

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, maxCount = 0;
  ll maxVal;
  unordered_map<ll, int> m;

  cin >> N;

  while(N--){
    ll num;

    cin >> num;

    if(m.count(num) == 0) m.insert({num, 1});
    else m[num]++;
  }

  for(auto e: m){
    if(e.second > maxCount || (e.second == maxCount && e.first < maxVal)){
      maxVal = e.first;
      maxCount = e.second;
    }
  }

  cout << maxVal;

  return 0;
}

/*
그냥 N(최대 10만)개의 수를 받고 그 중에서 제일 많이 나오는 수(공동 1등이 있으면 값이 작은 수)를 출력하면 된다. 근데 수의 범위가 매우 커서 
int로는 안 되고, long long을 써야 함. 그리고 int count[MAX] = {0} 이렇게 해서 count[i]: i가 등장한 횟수. 이렇게 할 수 없다. 왜냐? 
수의 범위가 크니까 배열 크기가 매우 커야 한다.

그래서 unordered_map을 썼다. 어떠한 수를 key, 등장 횟수를 value로 하여 맵을 쓰면 되고, 나중에는 26행처럼 iter로 돌면서 value가 가장 큰 
key를 출력하면 된다.

이렇게 푼 다음에, 맵 안 쓰고 그냥 벡터를 써서 풀기도 했음. 
*/