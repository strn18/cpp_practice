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