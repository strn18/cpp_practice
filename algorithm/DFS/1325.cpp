#include <iostream>
#include <vector>
#include <cstring>
#define MAX 10000

using namespace std;

vector<int> trust[MAX+1];
bool visited[MAX+1];

int countHack(int n);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, maxHack = 0;
  vector<int> maxHackNum;

  cin >> N >> M;

  while(M--){
    int A, B;

    cin >> A >> B;

    trust[B].push_back(A);
  }

  for(int i=1; i<=N; i++){
    memset(visited, false, sizeof(bool)*(N+1));

    int count = countHack(i);

    if(count > maxHack){
      maxHack = count;
      maxHackNum.clear();
      maxHackNum.push_back(i);
    }
    else if(count == maxHack)
      maxHackNum.push_back(i);
  }
  
  for(int i=0; i<maxHackNum.size(); i++)
    cout << maxHackNum[i] << ' ';

  return 0;
}

int countHack(int n){
  int count = 1;

  visited[n] = true;

  for(int i=0; i<trust[n].size(); i++){
    if(visited[trust[n][i]]) continue;

    count += countHack(trust[n][i]);
  }

  return count;
}

/*
처음에는 dp인 줄 알았음. int dp[i]: i를 해킹하면 해킹할 수 있는 컴퓨터의 개수. 로 잡고, 함수 DP(i)는 dp[i] != 0이면 dp[i]를 리턴하고, 
0이라면 우선 dp[i] = 1로 한 다음(자기 자신도 해킹되니까), trust[i]의 노드들의 dp값을 구해서 dp[i]에 더하여 dp[i]를 리턴하는 식으로 dp로 짰다. 
근데 시간초과가 남. 왜 그런가 생각해보니까, 사이클이 생기면 dp값을 영원히 구하지 못하고 무한루프에 빠진다. 1->2, 2->1일 때, DP(1)을 구하려면 
DP(2)를 구해야 하는데, 걔는 또 DP(1)을 구해야 하고, ... 반복. 

그래서 dfs로 바꿨다. 사실 처음에 dfs인가? 했는데 시간초과 날 것 같아서 패스했었다. 근데 문제를 잘 읽어보니 시간 제한이 5초로 넉넉해서 dfs로 
풀 수 있을 것이라고 판단, 1번부터 N번 노드에 대해 dfs를 실행해주고(이때, 실행 전 visited 배열을 false로 초기화한다), 그 값이 가장 큰 노드들을 
maxHackNum에 넣어서 출력하면 된다.

31행을 잘못 써서 틀렸던 거 빼면, 맞았다.
*/