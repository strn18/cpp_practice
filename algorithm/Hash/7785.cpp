#include <iostream>
#include <string>
#include <set>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  set<string, greater<string>> s1;

  cin >> N;

  while(N--){
    string name, info;

    cin >> name >> info;

    if(info =="enter") s1.insert(name);
    else s1.erase(name);
  }

  for(auto e: s1)
    cout << e << '\n';

  return 0;
}