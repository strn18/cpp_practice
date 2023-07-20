// 새로운 불면증 치료법(2. 비트연산)
#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  for(int tc=1; tc<=T; tc++){
    int N, check = 0;

    cin >> N;

    for(int i=1; true; i++){
      int num = N*i;

      while(num > 0){
        check |= (1 << (num % 10));
        num /= 10;
      }

      if(check == (1 << 10) - 1){
        cout << '#' << tc << ' ' << N*i << '\n';
        break;
      }
    }
  }

  return 0;
}