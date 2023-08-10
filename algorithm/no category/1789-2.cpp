#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N = 1;
  long long S, sum_to_N = 1;

  cin >> S;

  while(sum_to_N <= S)
    sum_to_N += (++N);
  
  cout << N-1;

  return 0;
}

/*
뇌절쳐서 파라메트릭 서치로 푼 1789를 다시 평범한 방법대로 풀었음. 그냥 N을 1부터 계속 증가시키면서, 1~N의 합이 S를 넘어갔다면 break 하고 N-1을
출력한다. 그리고 one_to_n 함수를 쓸 필요가 없는게, 그냥 어차피 N을 1부터 증가시킬 거니까 1~N의 합도 마찬가지로 걍 변수에 넣어놓고 N을 증가시킬
때마다 증가시킨 N 값을 거기에 더해주면 1~N의 합을 쉽게 구할 수 있음.
*/