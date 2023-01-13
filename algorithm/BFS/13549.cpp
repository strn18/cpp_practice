#include <iostream>
#include <string.h>
#include <queue>
#define MAX 100000

using namespace std;

int time[MAX+1];

void teleport(queue<int>& prev, int t);
void walk(queue<int>& prev, int t);

int main(){
  int N, K, count = 0;
  queue<int> pos;

  scanf("%d %d", &N, &K);

  memset(time, -1, (MAX+1)*sizeof(int));

  time[N] = count;
  pos.push(N);
  teleport(pos, count);

  while(time[K] == -1){
    count++;
    walk(pos, count);
    teleport(pos, count);
  }

  printf("%d", time[K]);  

  return 0;
}

void teleport(queue<int>& prev, int t){
  queue<int> next;

  while(!prev.empty()){
    int p = prev.front();
    prev.pop();
    next.push(p);

    if(p == 0) continue;

    p *= 2;
    while(p <= MAX){
      if(time[p] == -1){
        time[p] = t;
        next.push(p);
      }
      p *= 2;
    }
  }
  prev = next;
}

void walk(queue<int>& prev, int t){
  queue<int> next;

  while(!prev.empty()){
    int p = prev.front();
    prev.pop();

    if(p-1 >= 0 && time[p-1] == -1){
      time[p-1] = t;
      next.push(p-1);
    }
    if(p+1 <= MAX && time[p+1] == -1){
      time[p+1] = t;
      next.push(p+1);
    }
  }
  prev = next;
}

/*
다익스트라 문제 찾아 풀고 있었는데 이 문제 발견. 근데 bfs로 풀면 되지 않나? 싶어서 bfs로 풀어봤다.
원래 1697 숨바꼭질 문제는 수빈이의 걷기와 순간이동이 모두 1초가 걸리는데, 이 문제에서는 순간이동은 0초가 걸린다. 그렇기에 큐에 있는 원소들에 대해
+1, -1, *2 연산을 해주면서, 그게 not visited면 visited 체크 해주고 다시 큐에 집어넣는 과정을 반복하는, 원래 풀이로는 풀 수 없다(걷기는 +1초지만
순간이동은 +0초이다). 그래서, 큐에 있는 원소들에 대해서 걷기를 적용해주는 walk 함수와, 순간이동을 적용해주는 teleport 함수를 따로 만들었다.
그런 다음, 수빈이의 최초 위치인 N을 큐에 넣는다. 그리고 0초일 때 수빈이의 위치를 모두 구해주기 위해 teleport를 실행한다. 그 다음, 시간을 1초 
증가시키고, 1초일 때 수빈이의 최초 위치를 모두 구해서 큐에 넣어야한다. 이를 위해, 아까 0초일 때 위치들이 들어가있는 큐에 대해서 걷기를 적용해준다.
이렇게 하면, 0초일 때 위치에 +1이나 -1을 해서, 1초일 때 위치를 구해서 다시 큐에 넣을 수 있다. 그런 다음, 큐에 teleport를 적용한다. 0초일 때 
걸어서 1초일 때 위치를 큐에 넣었으니깐, 거기에 순간이동을 해주면 1+0 = 1초이다. 그렇기에 순간이동을 적용해준다. 이 과정을 반복한다. 

time[i]에는 수빈이가 i칸에 도달했을 때 시간이 들어있는데, 아직 도달 못했을 때는 -1로 초기화를 해줬다. 걷기나 순간이동을 적용한 위치의 time값이
-1이면 아직 도달 못한거니까 갱신해주고 큐에 위치값을 넣고, -1이 아니라면 이미 아까 갱신된 거니까(방문한 거니까) 패스. 이걸 반복하면서, time[K]이
갱신되면 그 값을 출력해주면 된다.
*/