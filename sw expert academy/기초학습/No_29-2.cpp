// 중간값 구하기(9. 해시)
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, M, count = 0;
    unordered_set<string> set1;
    string str;

    cin >> N >> M;

    for(int i=0; i<N; i++){
      cin >> str;
      set1.insert(str);
    }

    for(int i=0; i<M; i++){
      cin >> str;
      if(set1.find(str) != set1.end()) count++;
    }

    cout << '#' << t << ' ' << count << '\n';
  }

  return 0;
}

/*
unordered_set STL 사용하여 풀었다. 이 문제 같은 경우는, 어떠한 키값이 존재하는지만 알면 되고, 그 키값에 해당하는 value는 필요 없기 때문에 map이 
아닌 set을 사용하였다. 또한, 원소가 중복되지 않아 multiset이 아닌 set을 사용하였고, 내부 원소가 정렬될 필요가 없기에 일반 set이 아닌 
unordered_set을 사용하였다.

27행에서, M개의 각 문자열이 이전에 입력받은 N개의 문자열들 중에서 있는지 확인하기 위해 find 메소드를 사용했다. set1에 str이 존재한다면 
set1.find(str)는 그 위치의 내부 반복자(iterator)를 리턴하고, 존재하지 않는다면 set1.end()를 반환한다.
*/