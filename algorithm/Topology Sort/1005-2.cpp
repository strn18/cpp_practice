#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
#define MAX 1000

using namespace std;

int N, K, W;
int inDegree[MAX+1]; // 위상 정렬 시에 사용
vector<int> result;

void topologySort(vector<int> rule[]);

int main(){
  int T;

  scanf("%d", &T);
  while(T--){
    int time[MAX+1]; // time[i]: i번 건물 건설 시간
    int time_count[MAX+1]; // time_count[i]: i번 건물을 짓는데 걸리는 총 시간
    vector<int> rule[MAX+1];

    scanf("%d %d", &N, &K);

    memset(inDegree, 0, (N+1)*sizeof(int));
    result = vector<int>();

    for(int i=1; i<=N; i++){
      scanf("%d", &time[i]);
      time_count[i] = time[i];
    }

    for(int i=0; i<K; i++){
      int X, Y;
      scanf("%d %d", &X, &Y);
      rule[X].push_back(Y);
      inDegree[Y]++;
    }

    scanf("%d", &W);

    topologySort(rule);
    
    for(int i=0; i<result.size(); i++){
      int from = result[i];
      if(from == W) break;
      
      for(int j=0; j<rule[from].size(); j++){
        int to = rule[from][j];
        time_count[to] = max(time_count[to], time[to]+time_count[from]); // 더 긴 시간으로 갱신
      }
    }

    printf("%d\n", time_count[W]);
  }
  
  return 0;
}

void topologySort(vector<int> rule[]){
  queue<int> q;

  for(int i=1; i<=N; i++)
    if(!inDegree[i])
      q.push(i);
  
  while(!q.empty()){
    int x = q.front();
    q.pop();
    result.push_back(x);
    
    for(int i=0; i<rule[x].size(); i++){
      int y = rule[x][i];
      if(!(--inDegree[y]))
        q.push(y);
    }
  }
}

/*
원래 DP로 풀었던 1005번을 위상 정렬을 통해 다시 풀어보았다.
사실 좀 복잡했지만, 위상 정렬 부분을 제외하면 크게 어려운 부분은 없었다. 위상 정렬하는 방법은 큐를 통해 구현했는데,
https://m.blog.naver.com/ndb796/221236874984 여기를 참고했다. 

위상 정렬을 하고 나서 어떻게 풀어야할지 감이 안 잡혔는데, https://scarlettb.tistory.com/123 여기서 도움을 많이 얻었다.

핵심은, 위상 정렬이 된 노드들을 처음부터 탐색하면서, 어떠한 노드(건물)와 연결되어있는 노드(해당 건물을 지어야 지을 수 있는 건물)들의
time_count 값을 갱신해주면 된다. time_count[i]는, i번 건물을 짓기까지 걸리는 총 시간을 의미하는데, 이 시간을 최댓값으로 갱신해야한다.
가장 오래 걸리는 시간이 진짜 시간이니깐. 그러므로, time_count[to] = max(time_count[to], time[to]+time_count[from]) 가 성립된다(from은
어떠한 노드, to는 그 노드와 연결되어있는 노드). 이때 time_count의 값들은 모두 time 값과 똑같도록 초기화시켜줘야하는데, 왜냐면 위상 정렬
했을 때 첫 노드에 해당하는 놈들은 위의 식이 적용이 안 되므로, 값 갱신이 안 된다(0으로 남겠지). 근데 실제로는 걔(i번 노드라고 하면)를 짓는데
time[i] 만큼 걸리니까, 그걸로 초기화해줘야함.

그렇게 time_count를 W까지 갱신을 다 해주고나서, W 인덱스의 값을 출력해주면 된다. 근데 제출하니까 한 번 틀렸음 아마 개행을 안 해줘서 그런듯?
*/