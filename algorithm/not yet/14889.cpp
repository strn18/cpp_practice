/*
#include <iostream>
#include <vector>
#include <stdlib.h>
#define MAX 20

using namespace std;

int N;
int min_diff = 9999;
int stat[MAX][MAX];
vector<int> team_count[2];

void choose(int n, int team0, int team1);

int main(){
  scanf("%d", &N);
  
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &stat[i][j]);

  choose(0, 0, 0);
  printf("%d", min_diff);  
  return 0;
}

void choose(int n, int team0, int team1){
  int team_stat[2] = {team0, team1};

  for(int i=0; i<2; i++){
    if(team_count[i].size() < (N/2)){
      team_count[i].push_back(n);
      
      for(int j=0; j<team_count[i].size(); j++){
        int temp = team_count[i][j];
        team_stat[i] += (stat[n][temp]+stat[temp][n]);
      }
      
      if(n==N-1){
        min_diff = min(min_diff, abs(team_stat[0]-team_stat[1]));
      }
      else
        choose(n+1, team_stat[0], team_stat[1]);
      
      team_count[i].pop_back();
      team_stat[0] = team0;
      team_stat[1] = team1;
    }
  }
}

백트래킹 문제. 사실 별로 어려운 건 아닌데 두 부분에서 막힘이 있었다. 우선 처음에 코드를 짤
때, 35행의 for문에서처럼 팀에 n번 선수가 새로 왔으니까 stat을 갱신해주는 과정에서, 위의 코드처럼 그 팀의 선수를 담은 벡터를 돌면서 갱신해주는 게 아니라, 팀의 선수가 m명 있을 때 0번~m-1번 선수를 대상으로 갱신해주는 식으로 짜버렸다. 무슨 소리나면, 처음에는 team_count를 int형 배열로 만들었었는데, team_count[0]에는 0번 팀 선수의 수, [1]에는 1번 팀 선수의 수를 넣는 식으로 짰음. 이렇게 하고 32행 if문을 if(team_count[i] < (N/2))로 하는 식으로 한 것임. 근데 이런 다음에 그 밑 for문 부분에서 j는 [0, team_count[i])로 해놓고 temp 선언 부분 없이 바로 team_stat[i] += (stat[n][j]+stat[j][n])으로 했던가 그랬음. 이렇게 하니까 n번 선수의 소속팀과 관련 없느 선수와의 stat값을 더해줘버리는 일이 생긴 거임.
이거 고친 다음으로는, 예제 1번은 답이 맞는데 2번 3번은 이상하게 나오는 일이 발생했음. 이걸로 좀 오래 고민했는데 이유는 간단했다. team_count 벡터는 46행에서 값 되돌려놓기를 잘 했는데, team_stat 배열을 31행 for문에서 다시 한 번 쓴 다는걸 까먹고 그거 되돌려놓기를 안 함. 이렇게 하니까 n번 선수를 0번 팀에 넣으며 갱신된 0번 팀의 stat 값이 되돌려놓기가 안 돼서 1번 팀에 넣을 때 그 값을 그대로 쓰게 된 것임. 그렇게 하니까 min_diff 값이 제대로 안 나오게 되었고, 47~48행처럼 team_stat 배열을 원상태로 돌려놓는 부분 추가하니까 맞게 되었다.
어려운 건 아닌데 자꾸 별 거 아닌 부분에서 실수가 난다...
*/