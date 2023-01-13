#include <iostream>
#include <deque>
#define MAX 100000

using namespace std;

int main(){
  int N, K;
  int time[MAX+1];
  deque<int> pos;

  scanf("%d %d", &N, &K);

  for(int i=0; i<=MAX; i++)
    time[i] = -1;
  
  time[N] = 0;
  pos.push_front(N);

  while(!pos.empty()){
    int cur_pos = pos.front();
    int cur_time = time[cur_pos];
    pos.pop_front();

    if(cur_pos*2 <= MAX && time[cur_pos*2] == -1){
      time[cur_pos*2] = cur_time;
      pos.push_front(cur_pos*2);
    }
    if(cur_pos+1 <= MAX && time[cur_pos+1] == -1){
      time[cur_pos+1] = cur_time+1;
      pos.push_back(cur_pos+1);
    }
    if(cur_pos-1 >= 0 && time[cur_pos-1] == -1){
      time[cur_pos-1] = cur_time+1;
      pos.push_back(cur_pos-1);
    }
  }

  printf("%d", time[K]);

  return 0;
}

/*
0-1 BFS라는 개념으로 다시 한 번 풀어보았다. 사실 13549와 풀이가 크게 다르진 않고, 큐 말고 덱을 쓴다는 점이 다르다.
원래 13549에서는, 어떠한 시간 t초일 때, 큐에 가능한 위치값들을 넣어두고, t+1초가 됐을 때 그 위치값들을 순간이동 또는 걷기를 통해 바꿔주면서,
t+1초일 때 위치값들을 다시 큐에 넣어주는 그런 방식이었다.

이번에는 https://nicotina04.tistory.com/168 이 글을 보고, 0-1 BFS라는 개념을 통해 풀었다. 노드 사이 이동 비용이 0 또는 1일 때, 다익스트라보다
빠르게 푸는 방법이라고 한다. 방법은 간단한데, 덱에 위치값들을 넣고, 그 위치에서 인접 노드로 이동할 때 비용이 1이라면, 덱의 back에 푸시해준다.
비용이 0이라면, 덱의 front에 푸시해준다. 이때 인접 노드는, 위치+1, 위치-1, 위치*2 세 종류이고, time값이 아직 -1일 때만(그 위치에 아직 도달한
적이 없을 때만) time을 갱신하고 덱에 푸시해주면 된다.

제출해보니, 처음 BFS 방식이나 다익스트라로 풀었을 때보다 시간이 좀 줄었음을 확인.
*/