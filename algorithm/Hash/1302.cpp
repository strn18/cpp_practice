#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, ansCount = 0;
  string ansTitle;
  unordered_map<string, int> m;

  cin >> N;

  while(N--){
    string s;

    cin >> s;

    if(m.count(s) == 0) m[s] = 1;
    else m[s]++;
  }

  for(auto e: m){
    if(e.second > ansCount || (e.second == ansCount && e.first < ansTitle)){
      ansTitle = e.first;
      ansCount = e.second;
    }
  }

  cout << ansTitle;

  return 0;
}

/*
원래 unordered_map을 자주 써서 이번에도 그걸로 했는데, 생각해보니 그냥 map을 쓰면 27행에서 그냥 e.second > ansCount 이것만 해주면 된다. 
왜냐면 map이면 내부 원소를 key를 기준으로 오름차순 정렬 해주기 때문. 
*/