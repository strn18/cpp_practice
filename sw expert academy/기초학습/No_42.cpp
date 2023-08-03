// [S/W 문제해결 응용] 6일차 - K번째 접미어(12. 트라이)
#include <iostream>
#include <string>
#include <algorithm>
#define MAX 400

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int K, len;
    string str;
    string suffix[MAX];

    cin >> K;

    cin >> str;

    len = str.size();

    if(K > len){
      cout << '#' << t << ' ' << "none" << '\n';
      continue;
    }

    for(int i=0; i<len; i++){
      suffix[i] = "";

      for(int j=i; j<len; j++)
        suffix[i] += str[j];
    }

    sort(suffix, suffix+len);

    cout << '#' << t << ' ' << suffix[K-1] << '\n';
  }

  return 0;
}