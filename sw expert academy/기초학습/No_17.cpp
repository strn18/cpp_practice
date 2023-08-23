// 영준이의 진짜 BFS
#include <iostream>
#include <queue>
#include <vector>
#define MAX_N 100000
#define MAX_P 17 // log_2(100000) 반올림

using namespace std;

int parent[MAX_N+1][MAX_P+1]; // parent[i][j]: 노드 i의 2^j번째 부모. -1이면 없는 것.
vector<int> child[MAX_N+1];
int depth[MAX_N+1]; // depth[i]: 루트 노드의 depth가 0일 때, 노드 i의 depth. 

int findLCA(int a, int b); // a와 b의 가장 낮은 공통 조상을 리턴. 이때, a와 b의 depth는 같다.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  for(int t=1; t<=T; t++){
    int N;

    cin >> N;

    for(int i=2; i<=N; i++) // 우선 모두 -1로 초기화. 1번 노드(루트)의 부모는 참조할 일 없으므로 터치 x.
      for(int j=0; j<=MAX_P; j++)
        parent[i][j] = -1;
    
    for(int i=1; i<=N; i++)
      child[i].clear();

    for(int i=2; i<=N; i++){
      cin >> parent[i][0];
      child[parent[i][0]].push_back(i);
    }

    for(int j=1; j<=MAX_P; j++)
      for(int i=2; i<=N; i++)
        if(parent[i][j-1] != -1)
          parent[i][j] = parent[parent[i][j-1]][j-1]; // bottom-up 방식으로 parent를 채워준다.
    
    queue<pair<int, int>> Q; // {노드 번호, 노드의 depth}
    int prevNum = 1, prevDepth = 0; // 직전 방문 노드 번호, 직전 방문 노드 depth.
    long long distCount = 0;

    depth[1] = 0;

    for(int i=0; i<child[1].size(); i++)
      Q.push({child[1][i], 1});
    
    while(!Q.empty()){
      int curNum = Q.front().first;
      int curDepth = Q.front().second;

      Q.pop();

      depth[curNum] = curDepth; // 우선 depth를 채워줌.

      int LCA;

      if(curDepth == prevDepth + 1) LCA = findLCA(prevNum, parent[curNum][0]); // 부모 노드를 넣어줘서, 인자로 넣는 두 노드의 depth가 같도록 함.
      else LCA = findLCA(prevNum, curNum);

      distCount += (prevDepth - depth[LCA] + curDepth - depth[LCA]); // 직전 노드 -> LCA -> 이번 노드 로의 이동 거리.

      for(int i=0; i<child[curNum].size(); i++)
        Q.push({child[curNum][i], curDepth + 1});
      
      prevNum = curNum;
      prevDepth = curDepth;
    }

    cout << '#' << t << ' ' << distCount << '\n';
  }

  return 0;
}

int findLCA(int a, int b){
  if(a == b) return a;

  for(int j=MAX_P; j>=0; j--){ // 맨 위(2^17번째)의 부모부터, 바로 위 부모를 비교한다.
    if(parent[a][j] != -1 && parent[a][j] != parent[b][j]){ // 부모가 존재하고, 두 부모가 다르다면 거기로 이동(a, b 갱신).
      a = parent[a][j];
      b = parent[b][j];
    }
  }
  // 여기까지 왔을 때, a와 b의 부모는 반드시 같다. c가 부모일 때, 
  //   c
  //  a b 이러한 형태이다. 
  return parent[a][0];
}

/*
어려웠던 문제.

처음에는 이렇게 접근했다. 어떠한 노드(cur)를 탐색할 때, 바로 직전에 탐색했던 노드(prev)에서 cur로의 이동 거리는 얼마일까?
우선, 두 노드의 가장 낮은 공통 조상을 찾는다. 즉, 두 노드에서 위로 쭉쭉 올라가다가 처음으로 찾은 공통 조상이 바로 그것임.
그런 다음, 두 노드에서 그 공통 조상으로 올라오는 데 드는 거리를 합친다. 

이를 토대로 짜서 제출했다(첫번째, 두번째 제출). 근데 시간초과가 남. 생각해보면, 트리가 이진트리 같은 형태로 잘 짜였다면 logN 시간으로 
공통 조상을 찾을 수 있겠지만, 트리가 거의 일자로 나열되어 있는 형태라면, 하나하나 다 올라오면서 찾기 때문에 시간이 너무 많이 들게 된다.

고민하다가, 결국 찾아봤다. 그랬더니 LCA를 사용하는 문제라고 함. 그래서 https://blog.naver.com/kks227/220820773477 여기를 참고해서 
우선 공부해봤다. 그런 다음, 풀어봤는데 테케 59/61개 맞고 2개는 틀림. 뭐지? 하고 고민했는데, 알고보니 그냥 오버플로우였다. 
트리가 
   1
  2 3
 4   5
6     7
...
이런 형태라면? 2번 노드를 방문하는 데 1, 3번 노드를 방문하는 데 2, 4번 노드를 방문하는 데 3, ... 이니까, 총 
1+2+...+99999 = 4,999,950,000 를 이동하게 된다. 그래서 오버플로우가 난 것임.
long long으로 바꾸고 제출하니까 맞았다.

자세한 내용은 링크 및 주석 참조.
*/