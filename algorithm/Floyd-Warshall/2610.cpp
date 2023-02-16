#include <iostream>
#include <queue>
#include <algorithm>
#define MAX 100
#define INF 2100000000

using namespace std;

int dist[MAX+1][MAX+1];
int group[MAX+1] = {0};

void bfs(int N, int start, int num);

int main(){
  int N, M, a, b, groups = 0;
  int rep_num[MAX+1], longest_time[MAX+1];

  scanf("%d %d", &N, &M);

  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      dist[i][j] = (i==j ? 0 : INF);

  for(int i=0; i<M; i++){
    scanf("%d %d", &a, &b);
    dist[a][b] = 1;
    dist[b][a] = 1;
  }

  for(int i=1; i<=N; i++)
    if(group[i]==0)
      bfs(N, i, ++groups);

  for(int k=1; k<=N; k++){
    for(int i=1; i<=N; i++){
      if(dist[i][k] == INF) continue;
      for(int j=1; j<=N; j++){
        if(dist[k][j] == INF) continue;
        dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
      }
    }
  }

  for(int i=1; i<=groups; i++)
    longest_time[i] = INF;
  
  for(int i=1; i<=N; i++){
    int cur_time = 0, cur_group_num = group[i];

    for(int j=1; j<=N; j++)
      if(group[j] == cur_group_num)
        cur_time = max(cur_time, dist[i][j]);

    if(cur_time < longest_time[cur_group_num]){
      longest_time[cur_group_num] = cur_time;
      rep_num[cur_group_num] = i;
    }
  }

  printf("%d\n", groups);
  
  sort(rep_num+1, rep_num+1+groups);

  for(int i=1; i<=groups; i++)
    printf("%d\n", rep_num[i]);

  return 0;
}

void bfs(int N, int start, int num){
  queue<int> q;
  q.push(start);
  group[start] = num;

  while(!q.empty()){
    int cur = q.front();
    q.pop();

    for(int i=1; i<=N; i++){
      if(group[i]==0 && dist[cur][i]==1){
        q.push(i);
        group[i] = num;
      }
    }
  }
}

/*
다 풀어놓고 ㅈㄴ 어이없는 곳에서 막혀서 자꾸 틀렸던 플로이드 문제..
참석자들은 그룹을 형성하고 있다. 서로 알고 있는 참석자들은 같은 그룹이고, 그렇지 않다면 다른 그룹이다. 즉 사람이 7명이고 1-2 / 3-4 / 2-3 / 5-6
이렇게 서로 알고 있다면, 1, 2, 3, 4 가 한 그룹, 5, 6 이 한 그룹, 7 이 한 그룹이다. 즉 그룹(위원회)은 세 개가 있는 것이다. 이때 각 그룹 별로
대표를 선정해야하는데, 그 그룹 내의 참석자들의 의사전달시간 중 "최댓값이 최소가 되도록" 대표를 정해야한다.

우선 참석자들을 그룹짓는 것은 bfs로 해결했다. group[i]: i번 참석자의 그룹 번호. 로 두고, 30행에서 모든 참석자(1~N번)를 돌면서, 아직 그룹짓지
않았다면(group[i]==0), 걔를 시작으로 bfs를 쳐서 인접한 놈들로 계속 뻗어나가며 걔네들도 다 그룹지어준다. 그리고 그룹의 수는 groups에 저장한다.

그 다음, 참석자와 참석자가 몇 단계를 거쳐 연결되는지를 dist 배열에 저장했다. dist[i][j]: i번과 j번 참가자가 몇 단계로 이루어져있는지? 이다.
즉, 위의 예시에서는, 1번과 4번은 1-2-3-4 이렇게 연결되어있으니까 dist[1][4]나 dist[4][1]은 3이다. 1번과 5번은 연결되어있지 않으므로, 
dist[1][5]나 dist[5][1]은 INF이다. 이를 구하기 위해서 플로이드를 34~42행에 썼다. 여기까지는 문제가 없었음..

근데, 각 그룹에서 대표를 선정하는 과정에서, 문제를 잘못 이해하는 바람에 자꾸 60프로 정도에서 틀렸습니다가 떴다. 나는, 각 그룹의 "참가자들의
의사전달시간(참가자-대표 사이의 거리. 즉, dist[참가자][대표])의 합"이 최소가 되도록 대표를 선정하는 줄 알았는데, 자꾸 틀려서 질문 게시판에서
https://www.acmicpc.net/board/view/105382 이 글을 보고 문제를 다시 읽어보니, 각 그룹의 "참가자들의 의사전달시간의 최댓값"이 최소가 되도록
대표를 선정하는 것이었다. 이 두 가지는 비슷해보이지만(특히 주어진 예제에서는 둘 다 답이 똑같이 나옴) 차이가 있는데, 예를 들어 2610.png를 보자.
내가 처음에 풀었던 방식으로 답을 구하면, 이 그룹에서 대표는 3번 또는 4번이다(둘 다 의사전달시간의 합이 8이다. 근데 내 코드에서는 번호가 빠른
놈을 대표로 고르기 때문에 3번으로 고르긴 할 거임). 하지만, 문제 조건에 의하면, 대표는 4번이 되어야 한다. 대표가 3번일 때는 그룹 참가자들의 
의사전달시간의 최댓값이 3(1번-3번)이지만, 4번일 때는 2로 줄어든다. 그렇기에 대표는 3번이 아니라 반드시 4번이 되어야 한다.

이렇게 반례를 발견하고, 그에 맞게 플로이드 밑의 부분을 수정하니 맞았다. longest_time[i]: i번 그룹의 의사전달시간의 최댓값 이고, 
rep_num[i]: i번 그룹의 대표 번호 이다.

좀 까다롭지만 풀만한 문제였는데 문제 잘못 읽어서 질질 끌리니 아쉽네
*/