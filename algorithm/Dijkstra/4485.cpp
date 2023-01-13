#include <iostream>
#include <queue>
#define INF 2100000000
#define MAX 125

typedef struct{int row, col, distance;} box;

struct Compare{
  bool operator()(box a, box b){
    return a.distance > b.distance;
  }
};

using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int main(){
  for(int T=1; 1; T++){
    int N;
    int rupee[MAX][MAX], dist[MAX][MAX]; // rupee[i][j]: (i, j)의 도둑 루피 / dist[i][j]: (0, 0)에서 (i, j)로 가기 위해 먹는 최소 도둑 루피
    priority_queue<box, vector<box>, Compare> pq;

    scanf("%d", &N);
    if(N==0) break;

    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        scanf("%d", &rupee[i][j]);
        dist[i][j] = INF;
      }
    }

    dist[0][0] = rupee[0][0];
    pq.push({0, 0, dist[0][0]});

    while(!pq.empty()){
      int r = pq.top().row, c = pq.top().col, d = pq.top().distance;
      pq.pop();

      for(int i=0; i<4; i++){
        int temp_r = r+dr[i], temp_c = c+dc[i];

        if(0<=temp_r && temp_r<N && 0<=temp_c && temp_c<N){
          int temp_dist = d + rupee[temp_r][temp_c];

          if(temp_dist < dist[temp_r][temp_c]){
            dist[temp_r][temp_c] = temp_dist;
            pq.push({temp_r, temp_c, temp_dist});
          }
        }
      }
    }

    printf("Problem %d: %d\n", T, dist[N-1][N-1]);
  }

  return 0;
}

/*
처음으로 풀어본 다익스트라 문제. 차원이 2차원이고, 각 노드가 상하좌우로 연결되어있다는 점만 유의하면 기본적인 다익스트라 문제 같았다.

풀이 방법은 간단하다. 우선 2차원이라 노드를 단순 인덱스가 아닌, (행, 열)의 형태로 표현해야하기에 구조체를 사용했다(pair를 사용해도
되었겠지만, first second 쓰는 거 귀찮아서). 이후 다익스트라를 이용해서, 최단거리(여기서는 비용) 표인 dist를 갱신해주면 된다.

38행에서 while문을 돌릴 때, 큐에서 거리가 최소인 원소를 찾고, 그 원소의 인접 노드(칸)들의 dist를 갱신해주게 되는데, 이를 위해
큐에는 위치와 거리 정보를 모두 넣어주어야 하니까 아까 말했던 구조체를 (행, 열, 거리)의 정보를 담도록 선언했다. 그리고 시간복잡도를
줄이기 위해 우선순위 큐를 이용했고, 비교 기준은 원소들의 거리 값이다(오름차순). 그렇게해서 거리가 최소인 원소를 꺼냈다면, 인접 노드
(상하좌우 갈 수 있으니까 상하좌우 노드들이 되겠지)의 거리를 계산하면서, dist를 갱신해주고 갱신했다면 해당 정보를 다시 큐에 넣는다.

설명은 좀 복잡하지만, 사실 다익스트라의 기본적인 내용이라서 별로 어려울 건 없었다.

pq를 distance 기준 오름차순으로 정렬하기 위해 따로 Compare 구조체를 선언하였는데, 원래 sort 함수에서 정렬 기준 넣어줄 때 쓰던 
Compare은 함수여서 pq도 그렇게하면 되는 줄 알고 썼다가 오류 났다. pq는 저 자리에 함수가 들어가는 게 아니라, 구조체를 넣고 그 
구조체 안에는 operator라는 이름으로 연산자 오버로딩을 해줘야 함.
https://ansohxxn.github.io/cpp/chapter9-8/
여기를 보고 자세히 알 수 있었는데, 구조체 Compare을 함수처럼 Compare(a, b) 이렇게 동작할 때, 그 괄호 연산자를 오버로딩 하는듯.
Compare(a, b)가 호출되면, a.distance > b.distance 를 리턴하도록..
근데 왜 부등호 방향이 Compare 함수 쓸 때랑 반대인지는 잘 모르겠다.
*/