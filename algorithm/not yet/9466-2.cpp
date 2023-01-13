/*
#include <iostream>
#include <stack>

using namespace std;

int student[100001];
int status[100001];
int no_team;
stack <int> cycle;

void DFS(int n);

int main(){
  int T, n;
  cin >> T;

  for(int i=0; i<T; i++){
    cin >> n;
    no_team = 0;
    for(int j=1; j<=n; j++){
      cin >> student[j];
      status[j] = 0;
    }
    
    for(int j=1; j<=n; j++)
      if(!status[j])
        DFS(j);
    
    cout << no_team << endl;
  }
  
  return 0;
}

void DFS(int n){
  if(status[n]==0){ // 학생 n은 아직 계산 안 됨
    cycle.push(n);
    status[n] = 1;
    DFS(student[n]);
    return;
  }
    
  else if(status[n]==1){ // 학생 n은 계산 중인 상태(사이클 도는 중)
    while(cycle.top()!=n){ // 사이클 위에서부터 팀에 소속된다
      status[cycle.top()] = -1;
      cycle.pop();
    } // 학생 n까지는 팀에 소속됨
    status[n] = -1;
    cycle.pop();
  }
  // 그 밑으로는 팀에 소속 안 됨(status가 -1일 때는 여기로 바로 오는데, 그 때는 사이클 도는 학생 모두가 팀에 소속 안 되기 때문임)
  no_team += cycle.size();
  while(cycle.size()!=0){
    status[cycle.top()] = -1;
    cycle.pop();
  }
}

다시 푼 문제 4. 원래 풀이랑 구조적으로는 큰 차이는 없으나 세부적으로 좀 차이가 있었음. 원래 풀이에서는 각 학생이 가리키는 학생 정보가 담긴 벡터를 만들고, 사이클을 발견하면 가리키는 학생을 따라가며 벡터 안을 직접 돌면서 cur학생(이 코드로 치면 n학생)을 찾을 때까지 cnt(팀에 소속한 학생 수)를 증가시키는 방식으로 풀었었다. 근데 이번 풀이에서는 가리키는 학생 정보는 int 배열에 담고, 현재 사이클을 담는 용도로 스택을 하나 만듦. 그 다음 스택에서 사이클을 발견하면 n학생이 나올 때까지 pop을 한 다음에 남은 학생(팀에 못 낀 학생)들 수를 no_team에 추가해주는 방식으로 풀었다. 
방식 자체는 크게 다르지 않으나, 원래 풀이는 벡터만 썼고 cur학생을 찾는 것도 for문으로 벡터를 도는 방식이었는데, 이번 풀이에서는 int 배열이랑 스택 두 개를 쓴데다가 하나하나 pop을 하는 방식이라, 원래 풀이가 훨씬 간결한 것 같다. 그리고 status(원래 풀이의 visit)을 최신화해주는 과정도 이번 풀이에서는 pop을 할 때 바꿔주는 방식인데, 원래 풀이에서는 DFS 함수 끝에서 일괄적으로 바꿔주는 식이라 더 깔끔했다. 그래도 원래 풀이는 알고리즘 수업에서 배웠던 풀이인데 이번엔 자력으로 비슷한 풀이 찾은 거니깐 좋은 거지 뭐 ㅋ
*/