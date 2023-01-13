/*
#include <iostream>
#include <queue>

using namespace std;

int M, N, day_count=0;
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int box[1000][1000];
queue <pair<int, int>> tomato_q, temp_q;

void BFS();

int main(){
  cin >> M >> N;
  
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++){
      cin >> box[i][j];
      if(box[i][j]==1)
        tomato_q.push(pair<int, int>(i, j));
    }

  BFS();

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      if(box[i][j]==0){
        cout << -1;
        return 0;
      }
  cout << day_count;
  return 0;
}

void BFS(){
  int r, c;
  while(!tomato_q.empty()){
    r = tomato_q.front().first;
    c = tomato_q.front().second;

    for(int i=0; i<4; i++)
      if(0<=r+dy[i] && r+dy[i]<N && 0<=c+dx[i] && c+dx[i]<M)
        if(box[r+dy[i]][c+dx[i]]==0){
          temp_q.push(pair<int, int>(r+dy[i], c+dx[i]));
          box[r+dy[i]][c+dx[i]] = 1;
        }
    
    tomato_q.pop();
  }
  
  if(temp_q.empty())
    return;
  
  day_count++;
  tomato_q = temp_q;
  temp_q = queue<pair<int, int>>();
  BFS();
}

1012에 이어 두 번째로 다시 푼 문제. 근데 저번 풀이랑 약간 달라졌다. 저번 풀이에서는 토마토 익는 과정 계산하는 부분이 BFS 함수 말고 main 함수에서도 좀 자잘하게 포함되어 있었음. 근데 이번 풀이에서는 깔끔하게 싹 다 BFS 함수 안에서만 계산하고, main에서는 토마토 입력받고 날짜 출력하는 것만 다뤄서 풀이가 좀 더 깔끔해진듯. 그리고 저번이랑 거의 똑같은 이유로 메모리 초과가 났는데, 이번에는 '다음 날에 익을 토마토의 위치를 구해서 temp_q에 푸시하는 과정'(43행의 for문) 끝 부분에서 그 위치의 box 값을 1로 미리 바꾸어주는 방식으로 좀 더 간결하게 해결했음.
*/