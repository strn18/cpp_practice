// 염라대왕의 이름 정렬(10. 분할정복)
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#define MAX 20000

using namespace std;

bool compare(string n1, string n2);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N;
    unordered_set<string> name_set;
    vector<string> names;

    cin >> N;

    for(int i=0; i<N; i++){
      string name;

      cin >> name;

      if(name_set.find(name) == name_set.end()){
        name_set.insert(name);
        names.push_back(name);
      }
    }

    sort(names.begin(), names.end(), compare);

    cout << '#' << t << '\n';

    for(int i=0; i<names.size(); i++)
      cout << names[i] << '\n';
  }

  return 0;
}

bool compare(string n1, string n2){
  if(n1.size() != n2.size()) return n1.size() < n2.size();
  else return n1 < n2;
}

/*
우선 중복된 이름을 받지 않기 위해, unordered_set을 사용하였다. 해당 세트에 이름이 없다면 insert한 후 names 벡터에 이름을 넣는다. 세트에 이름이 
있다면, 중복을 피하기 위해 벡터에 넣지 않는다.

이후 벡터를 정렬하는데, 1) 이름이 짧은 게 먼저, 2) 이름이 같으면 사전 순으로 앞서는 게 먼저. 이 규칙으로 정렬한다.

중복된 원소를 제거할 때, unique 함수와 erase 함수를 사용할 수 있다고 한다. https://dpdpwl.tistory.com/39 참고.
*/