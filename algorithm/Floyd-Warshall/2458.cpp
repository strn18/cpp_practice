#include <iostream>
#define MAX 500

using namespace std;

int N;
bool dist[MAX+1][MAX+1] = {false};

bool check(int start);

int main(){
  int M, a, b, count = 0;

  scanf("%d %d", &N, &M);

  for(int i=0; i<M; i++){
    scanf("%d %d", &a, &b);
    dist[a][b] = true;
  }

  for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
      if(!dist[i][k]) continue;

      for(int j=1; j<=N; j++)
        if(dist[k][j])
          dist[i][j] = true;
    }
  }

  for(int i=1; i<=N; i++)
    if(check(i)) count++;

  printf("%d", count);

  return 0;
}

bool check(int start){
  for(int i=1; i<=N; i++){
    if(i==start) continue;
    if(!dist[start][i] && !dist[i][start]) return false;
  }
  
  return true;
}

/*
오랜만에 풀었던 플로이드 와샬 문제. 처음엔 좀 헷갈렸는데 그리 어렵진 않았음.

문제를 살짝 꼬아놨는데, A노드에서 B노드로 갈 수 있다면 A학생이 B학생보다 키가 작다고 확신할 수 있다. 그렇기에, 어떠한 노드에서 다른 노드로
갈 수 있는지를 플로이드를 통해 모두 구해준다. 그 다음, 어떤 노드가 다른 모든 노드와 연결되어 있을 경우(어떤 노드가 다른 노드로 갈 수 있거나
그 반대일 경우 연결되어 있는 것임), 그 노드에 해당하는 학생의 키 순서를 확신할 수 있다.

처음에는, a b 가 주어지면 dist[a][b] = 1, dist[b][a] = -1로 잡고, 나중에 플로이드를 칠 때 dist[i][k]*dist[k][j]가 1일 때만 갱신해주는 식으로 
할까? 싶었다. 근데 그렇게 하면, 정점이 최대 500개인데 O(n^3)인 플로이드를 치면 시간초과가 날 것 같았음. 그래서 어떻게 좀 줄여볼 수 있을까 생각을
해봤는데, 생각해보니깐 dist[a][b]가 1이든 -1이든, 어쨌든 0(가는 길 없음)만 아니라면, dist[b][a]는 안 구해도 a와 b가 연결되어있다는 것을 알 수
있음. 그렇기 때문에, 굳이 쓸데 없이 1과 -1 이렇게 구할 필요 없이, 그냥 a b 가 주어지면 dist[a][b]만 1로 잡고 플로이드를 쳐주면 된다. 그래서
dist의 타입도 그냥 bool로 잡았다.

23행에서 dist[i][k]가 false면 i에서 k로는 못 가는 거니까, continue해준다. 26행에서 dist[k][j]가 true면, dist[i][k]와 dist[k][j]가 true니까,
dist[i][j]도 true라고 할 수 있다(즉 i노드에서 j노드로 연결되어 있다. i학생이 j학생보다 키가 작다). 플로이드가 끝나고 나서, 32행에서 모든 노드에
대해 check를 해준다. start노드가 자신 제외 모든 노드와 연결되어 있다면(방향 상관 없음. start->i이거나(start학생이 i학생보다 키 작음), i->start
이거나(i학생이 start학생보다 키 작음) 상관 없다), true를 리턴한다. 그걸 다 세주면 답이 된다.
*/