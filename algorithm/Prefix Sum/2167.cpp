#include <iostream>
#define MAX 300

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, K;
  int p_sum[MAX+1][MAX+1] = {0};

  cin >> N >> M;
  for(int i=1; i<=N; i++){
    for(int j=1; j<=M; j++){
      cin >> p_sum[i][j];
      p_sum[i][j] += p_sum[i][j-1]+p_sum[i-1][j]-p_sum[i-1][j-1];
    }
  }

  cin >> K;
  while(K--){
    int i, j, x, y;

    cin >> i >> j >> x >> y;
    cout << p_sum[x][y]-p_sum[x][j-1]-p_sum[i-1][y]+p_sum[i-1][j-1] << '\n';
  }

  return 0;
}

/*
기초적인 2차원 누적 합 문제
*/