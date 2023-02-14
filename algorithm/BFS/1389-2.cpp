#include <iostream>
#include <queue>
#define MAX 100

using namespace std;

int N, M, min_bacon = 999, min_num = 0;
bool connected[MAX+1][MAX+1] = {false};

void count_bacon(int start);

int main(){
  int A, B;

  scanf("%d %d", &N, &M);

  for(int i=0; i<M; i++){
    scanf("%d %d", &A, &B);
    connected[A][B] = true;
    connected[B][A] = true;
  }

  for(int i=1; i<=N; i++)
    count_bacon(i);

  printf("%d", min_num);

  return 0;
}

void count_bacon(int start){
  int count = 0;
  int bacon[MAX+1] = {0};
  queue<int> q;
  q.push(start);

  while(!q.empty()){
    int cur_num = q.front();
    int cur_bacon = bacon[cur_num];
    q.pop();

    for(int j=1; j<=N; j++){
      if(j!=start && connected[cur_num][j] && !bacon[j]){
        bacon[j] = cur_bacon + 1;
        q.push(j);
      }
    }
  }

  for(int i=1; i<=N; i++)
    count += bacon[i];

  if(count < min_bacon){
    min_bacon = count;
    min_num = start;
  }
}

/*
https://hackids.tistory.com/m/86 여기를 보고 1389를 bfs로도 풀어보았음. count_bacon은 start가 다른 사람들과 연결된 단계를 구하고 이를 통해 
start의 케빈 베이컨 수를 구하여 min_bacon과 min_num을 갱신하는 함수로, bfs로 구현했다.
우선 bacon 배열은 start가 다른 사람들과 몇 단계로 연결됐는지 나타낸다. 이를 처음에는 아직 연결 안 되었다는 뜻으로 0으로 초기화한다.
그 다음, 큐에 start를 넣으면서 bfs를 시작한다. bfs는 큐의 front를 뽑아 cur_num에 넣고 그 값의 bacon 값을 cur_bacon에 저장한다. 그 다음, 
1~N번 사람을 돌면서, cur_num과 연결되어있고 아직 bacon을 구하지 않았다면, 그 놈의 bacon은 이제 cur_bacon+1 이다(cur_num은 start와 cur_bacon
단계로 연결되었고, 그 놈은 다시 cur_num과 인접하니까 +1). 그리고 그 놈을 다시 큐에 넣어주면 된다. 이때, start의 bacon 값은 구할 필요가 없으므로
제외한다. 이렇게 start를 제외한 모든 사람에 대해 bacon값을 구한 다음, 그걸 모두 더해서 케빈 베이컨 수를 구하고 이걸로 갱신해주면 됨.
*/