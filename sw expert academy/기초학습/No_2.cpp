// 이진수 표현(2. 비트연산)
#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, M;
    bool flag = true;

    cin >> N >> M;

    for(int i=0; i<N; i++){
      if((M & (1 << i)) == 0){
        flag = false;
        break;
      }
    }

    cout << '#' << t << ' ' << (flag ? "ON" : "OFF") << '\n';
  }

  return 0;
}