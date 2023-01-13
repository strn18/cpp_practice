#include <iostream>
#include <string.h>
#include <queue>
#define INF 2100000000
#define MAX 100000

using namespace std;

int main(){
  int N, K;
  int dist[MAX+1];

  scanf("%d %d", &N, &K);

  for(int i=0; i<=MAX; i++)
    dist[i] = INF;
  dist[N] = 0;

  priority_queue<pair<int, int>> pq;
  pq.push({dist[N], N});

  while(!pq.empty()){
    int cur_dist = -pq.top().first;
    int cur_pos = pq.top().second;
    pq.pop();

    if(dist[cur_pos] < cur_dist) continue;

    if(cur_pos+1 <= MAX && cur_dist+1 < dist[cur_pos+1]){
      dist[cur_pos+1] = cur_dist+1;
      pq.push({-dist[cur_pos+1], cur_pos+1});
    }
    if(cur_pos-1 >= 0 && cur_dist+1 < dist[cur_pos-1]){
      dist[cur_pos-1] = cur_dist+1;
      pq.push({-dist[cur_pos-1], cur_pos-1});
    }
    if(cur_pos*2 <= MAX && cur_dist < dist[cur_pos*2]){
      dist[cur_pos*2] = cur_dist;
      pq.push({-dist[cur_pos*2], cur_pos*2});
    }
  }

  printf("%d", dist[K]);

  return 0;
}

/*
다익스트라로 푼 13549문제. i번 칸이 있을 때, i+1, i-1칸과는 비용 1로 연결되어있고, i*2번 칸과는 비용 0으로 연결되어있다고 생각하고 다익스트라로
풀면 된다. 
원래 15행에서 dist를 INF로 초기화할 때, 별 생각 없이 memset을 써서 초기화하려했는데, 값들이 INF로 초기화가 잘 안 됐음. 알고보니까 memset은
1바이트 단위(char값)로 값을 초기화해서, 각 칸의 값이 1바이트 기준으로 초기화가 됨. 그래서 제대로 안 되었던 것. 문자열이나 char 배열에서 값을 
수정하거나, 숫자 배열에서 0으로 초기화할 때 주로 쓴다고 한다. 근데 이 문제 첫번째 풀이에서 -1로 초기화할 때는 제대로 되었었음.. 확인해보니까
0이랑 -1은 제대로 되는데, -2부터 안 된다. 그냥 앞으로 0으로 초기화하는 거 아니면 굳이 쓰지 말아야겠다.
https://blockdmask.tistory.com/441
*/