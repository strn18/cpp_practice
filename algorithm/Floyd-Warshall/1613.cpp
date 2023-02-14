#include <iostream>
#define MAX 400

using namespace std;

bool relate[MAX+1][MAX+1] = {false};

int main(){
  int N, K, S, first, next;

  scanf("%d %d", &N, &K);
  for(int i=0; i<K; i++){
    scanf("%d %d", &first, &next);
    relate[first][next] = true;
  }

  for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
      if(!relate[i][k]) continue;

      for(int j=1; j<=N; j++){
        if(!relate[k][j] || i==j) continue;
        
        relate[i][j] = true;
      }
    }
  }

  scanf("%d", &S);
  for(int i=0; i<S; i++){
    scanf("%d %d", &first, &next);

    if(relate[first][next])
      printf("-1\n");
    else if(relate[next][first])
      printf("1\n");
    else
      printf("0\n");
  }

  return 0;
}

/*
어려워보였으나 플로이드-와샬로 푸니 쉬웠던 문제. 
전후사건이 (a, b)로 주어진다. 그러면, a노드 -> b노드 방향으로 연결되었다고 생각한다(b -> a 방향으로는 연결 x).
입력을 모두 받은 후, 이를 바탕으로 플로이드를 친다. 그 결과, i노드 -> j노드 방향으로의 경로값이 존재한다면 i사건이 j사건보다 먼저 일어났다는
것을 확정할 수 있다. 만약 경로값이 존재하지 않는다면, 전후 관계를 알 수 없다. 즉, 경로값을 담는 배열을 dist라고 한다면, dist[i][j]와 dist[j][i]가
둘 다 값이 없다면(INF라면) i와 j의 전후 관계를 알 수 없는 것이다.

이걸 바탕으로 플로이드-와샬을 치려고 했는데, 생각해보니까 i -> j로 연결되었다면, 경로값이 존재한다는(INF가 아니라는) 것이 중요한 것이지, 그 값이
얼마인지는 중요하지 않다. 그렇기에, 경로값을 담는 배열을 굳이 int형으로 할 필요 없이, 그냥 bool형으로 해도 되지 않나? 싶었다.

그래서 경로값을 담는 배열을 bool형으로 relate라고 설정했다. relate[i][j]가 true라면 i -> j 순으로 일어난 것이다.
우선 입력을 받은 후, 플로이드를 친다. i와 j의 중간 노드를 k라 하면, i -> k와 k -> j 두 경로가 모두 가능할 때만 24행으로 내려간다. 즉, 
relate[i][k] 또는 relate[k][j]가 false라면 continue 한다. i==j 일 때도 의미 없으므로 제외. 그러다가 24행에서, relate[i][j] = true로 만들어준다.
i->k이고, k->j이니까, i->j임을 확신할 수 있기 때문이다. 

플로이드가 끝나면, 전후 관계를 알고 싶은 사건을 입력받아준다. 두 사건을 (c, d)라고 하면, relate[c][d]가 true면 c->d이다. 반대로 relate[d][c]가
true면 d->c이다. 둘 다 false면 전후 관계를 알 수 없다.
*/