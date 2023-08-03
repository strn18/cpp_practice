// [S/W 문제해결 응용] 6일차 - K번째 문자열(12. 트라이)
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int K;
    string str;
    unordered_set<string> sub_set;
    vector<string> sub_vec;

    cin >> K >> str;

    for(int len=1; len<=str.size(); len++){
      for(int start=0; start+len<=str.size(); start++){
        string sub = str.substr(start, len);

        if(sub_set.find(sub) == sub_set.end()){
          sub_set.insert(sub);
          sub_vec.push_back(sub);
        }
      }
    }

    sort(sub_vec.begin(), sub_vec.end());

    cout << '#' << t << ' ' << (K > sub_vec.size() ? "none" : sub_vec[K-1]) << '\n';
  }

  return 0;
}