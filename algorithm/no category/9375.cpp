#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int n, ans = 1;
    vector<pair<string, int>> cloth;

    cin >> n;

    for(int i=0; i<n; i++){
      string name, type;
      bool new_type = true;

      cin >> name >> type;

      for(int j=0; j<cloth.size(); j++){
        if(cloth[j].first == type){
          cloth[j].second++;
          new_type = false;
          break;
        }
      }

      if(new_type)
        cloth.push_back({type, 1});
    }

    for(int i=0; i<cloth.size(); i++)
      ans *= (cloth[i].second+1);
    
    cout << ans-1 << '\n';
  }

  return 0;
}

/*
입을 수 있는 총 가짓수는, 의상의 종류 별 의상 개수+1을 다 곱해주고, 거기서 1을 빼주면 된다(아무것도 안 입은 경우는 제외하므로).

pair와 vector를 써서 구현했다. pair의 first는 의상의 종류이고, second는 개수임. 이미 있는 의상 종류라면 개수만 +1해주면 되고, 없으면 새로
만들어서 벡터에 넣어준다.

map을 이용하면 더 쉽게 풀 수 있음.
*/