#include <iostream>
#define MAX 100000

using namespace std;

int p_sum[MAX+1][3] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, Q, num;

  cin >> N >> Q;

  for(int i=1; i<=N; i++){
    for(int j=1; j<=3; j++)
      p_sum[i][j-1] = p_sum[i-1][j-1];

    cin >> num;
    p_sum[i][num-1]++;
  }
  
  while(Q--){
    int a, b;

    cin >> a >> b;

    for(int j=1; j<=3; j++)
      cout << p_sum[b][j-1]-p_sum[a-1][j-1] << ' ';

    cout << '\n';
  }

  return 0;
}

/*
기초적인 구간 합 문제.
*/