/*
#include <iostream>
#include <vector>

using namespace std;

int N, result = 0;
vector<pair<int, int>> queen;

void N_Queen(int row);
int Able_Attack(pair<int, int> new_queen);
int Check(pair<int, int> q1, pair<int, int> q2);

int main(){
  cin >> N;

  N_Queen(0);

  cout << result;

  return 0;
}

void N_Queen(int row){
  for(int col=0; col<N; col++){
    pair<int, int> new_queen = make_pair(row, col);
    if(Able_Attack(new_queen)) // 이번 퀸이 기존 퀸을 공격 가능한 경우
      continue;
    if(row==N-1){ // 공격 가능하지 않고, 이번이 마지막 행일 경우
      result++;
      continue;
    }
    queen.push_back(new_queen); // 마지막 행이 아니면 기존 퀸에 이번 퀸을 추가
    N_Queen(row+1); // 다음 행 계산
    queen.pop_back(); // 기존 퀸에서 이번 퀸 다시 빼주기
  }
}

int Able_Attack(pair<int, int> new_queen){
  for(int i=0; i<queen.size(); i++)
    if(Check(queen[i], new_queen))
      return 1;
  return 0;
}

int Check(pair<int, int> q1, pair<int, int> q2){
  if(q1.second == q2.second) return 1;
  if(q1.first+q1.second == q2.first+q2.second) return 1;
  if(q1.first-q1.second == q2.first-q2.second) return 1;
  return 0;
}

백트래킹 배우며 소개된 문제. 풀이 전 혼자 풀어보았다. 처음에는 체스판을 의미하는 2차원 int 배열인 pos(퀸이 그 자리에 있으면 값이 1)를 만들고, col이 for문을 돌아가면서 pos[row][col]=1을 해준 후 pos를 이용하여 퀸들이 해당 위치일 때 공격가능한지 탐색하는 식으로 짜려 했음. 근데 매번 그렇게 체스판을 탐색하면 시간초과 날 것 같아서 다른 방법을 생각했는데, 퀸을 새로 놓을 때마다 해당 퀸이 공격 가능한 자리를 2차원 int 배열인 attack_pos에 표시(해당 자리를 공격 가능하면 값이 1)하고, 다음 퀸은 attack_pos[row][col]이 0이면 거기에 두고, 해당 퀸이 공격 가능한 자리를 attack_pos에 다시 표시하여 갱신하는 방식을 생각해봤다. 그러나 해당 위치의 퀸 탐색 후 백트래킹하는 과정에서 attack_pos를 다시 원래대로 돌려놓아야 하는데, 그 방법이 마땅치 않아서 포기.
다시 처음 방법을 생각해봤는데, 2차원 int 배열인 pos에 퀸 자리를 1로 표시하는 방식 말고, 애초에 퀸의 위치를 pair형 vector에 집어넣는 방식을 생각해봄. 즉 "해당 체스판에서 퀸들은 서로 공격 가능한지"가 아니라 "이번 퀸은 기존 퀸을 공격 가능한지"로 짜보았다. 이를 판별하기 위한 Check 함수 부분에서, 퀸의 공격 범위 중 우상향과 우하향 대각선을 탐지하는게 이상하게 잘 안 떠올라서.. 머리를 싸맸는데 x+y 값이 같거나(우하향) x-y 값이 같으면(우상향) 대각선 범위에 있는 것이었다. 
지금 코드는 두 번째 제출 코드인데, 첫 번째 제출에서는 new_queen을 따로 만들지 않고 int형인 row와 col을 Able_Attack에 직접 넘겨주고, queen에도 직접 push하는 식으로 짰었다. 지금 코드가 보기는 더 좋지만 첫 번째 제출 코드가 시간은 더 짧았다. make_pair를 자주 안 하면 실행 시간이 더 짧아질 것이라 생각했는데, 왜 더 길어졌는지는 잘 모르겠다..
강의에서 보여준 코드는, pair형 vector를 사용하지 않고 arr[depth] = i에서, depth가 row, i가 col 역할을 했음. 즉 벡터 대신에 배열을 사용한 셈. 그리고 Able_Attack과 Check를 합쳐서 짧게 줄였고, N_Queen을 long long형으로 해서 끝에서 값을 리턴하며 더해나가는 방식이었다.
*/