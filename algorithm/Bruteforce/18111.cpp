#include <iostream>
#define MAX 500
#define INF 2100000000

using namespace std;

int N, M, B;
int board[MAX][MAX];

int make_flat(int h);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int sum = 0;

  cin >> N >> M >> B;

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      cin >> board[i][j];
      sum += board[i][j];
    }
  }
  
  int low = sum / (N*M), high = (sum+B) / (N*M);
  int min_time = INF, ans;

  for(int h=low; h<=high; h++){
    int time = make_flat(h);

    if(time <= min_time){
      min_time = time;
      ans = h;
    }
  }
  
  cout << min_time << ' ' << ans;

  return 0;
}

int make_flat(int h){
  int count = 0;

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      if(board[i][j] <= h) count += (h - board[i][j]);
      else count += 2*(board[i][j] - h);
    }
  }

  return count;
}

/*
다른 풀이 보니깐 그냥 완전 브루트포스로도 풀 수 있는 문제였음.

모든 높이(0~256)에 대해서 땅고르기를 다 시도해보고, 가능한 높이(주어진 땅과 블록으로 그 높이를 맞출 수 없을 수도 있으니깐) 중에서 실행 
시간이 최소이며, 그게 여러 개면 높이가 가장 높은 것을 답으로 찾는, 단순한 브루트포스로도 풀 수 있었다.

나는 주어지는 board가 500*500이고, 높이가 256까지라면 대충 500*500*256 = 6400만이길래, 시간초과 나는 거 아닌가 싶어서 다르게 풀었다.

잘 생각해보면, 굳이 모든 높이를 다 볼 필요는 없다. 주어진 땅에 있는 블록의 개수의 총합(각 칸의 높이의 총합)을 N*M으로 나눈 몫부터, 
그 총합에 B를 더한 값을 N*M으로 나눈 몫 사이의 값들만을 높이로 하여 살펴보면 된다. 왜냐? 가령 주어진 땅이 3 2 5라면, 10/3 = 3 높이가 
최선의 경우이다. 왜냐? 그거보다 높이는 못 쌓고(블록 부족), 그거보다 낮게 쌓으려면 더 깎아야 하는데, 깎는 데는 2초가 걸리니까 손해임. 
그렇기에 상술한 경우만 보면 더 효율적으로 찾을 수 있다.
*/