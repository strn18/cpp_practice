#include <iostream>
#include <vector>
#include <queue>
#define MAX 32000

using namespace std;

int main(){
  int N, M;
  int inDegree[MAX+1] = {0}; // 위상 정렬할 때 사용(inDegree[i]는 i를 가리키는 노드의 수(i보다 앞에 서는 학생의 수)를 의미함)
  vector<int> seq[MAX+1]; // seq[i]에 j가 있다면, i 뒤에 j가 와야함을 의미함.
  queue<int> q; // 위상 정렬할 때 사용
  
  scanf("%d %d", &N, &M);

  for(int i=0; i<M; i++){
    int A, B;
    scanf("%d %d", &A, &B);
    seq[A].push_back(B);
    inDegree[B]++;
  }
  
  for(int i=1; i<=N; i++)
    if(!inDegree[i])
      q.push(i);
    
  while(!q.empty()){
    int cur = q.front();
    q.pop();
    printf("%d ", cur);
        
    for(int i=0; i<seq[cur].size(); i++)
      if(!(--inDegree[seq[cur][i]]))
        q.push(seq[cur][i]);
  }
    
  return 0;
}

/*
위상 정렬을 구현할 줄만 알면 어렵지 않았던 문제. 입력으로 (A B)가 주어지면, A 뒤에 B가 서야한다. 이를 이용하여, A -> B의 형태(A와 B 사이의 간선이
B를 가리키는 방향)라고 생각하고, 위상 정렬을 해준 다음 맨 처음 노드부터 출력해주면 된다(정답이 여러 개일 수 있음).
위상 정렬은, 1005-2에서 했던 것처럼 큐를 이용한 bfs 방식으로 해주었다. 
*/