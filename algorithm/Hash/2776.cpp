#include <iostream>
#include <unordered_set>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int N, M, num;
    unordered_set<int> s;

    cin >> N;

    while(N--){
      cin >> num;
      s.insert(num);
    }

    cin >> M;

    while(M--){
      cin >> num;
      cout << (s.count(num) != 0 ? 1 : 0) << '\n';
    }
  }

  return 0;
}

/*
해시 or 이분탐색으로 풀 수 있는 문제. 
*/